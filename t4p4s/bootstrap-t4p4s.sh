
# Highlight colours
cc="\033[1;33m"     # yellow
nn="\033[0m"

APPROX_INSTALL_MB="2500"
FREE_MB="`df --output=avail -m . | tail -1 | tr -d '[:space:]'`"

if [ "$SKIP_CHECK" != "1" ] && [ "$FREE_MB" -lt "$APPROX_INSTALL_MB" ]; then
    echo -e "Bootstrapping requires approximately $cc$APPROX_INSTALL_MB MB$nn of free space"
    echo -e "You seem to have $cc$FREE_MB MB$nn of free space on the current drive"
    echo -e "To force installation, run ${cc}SKIP_CHECK=1 $0$nn"
    exit
else
    echo -e "Installation will use approximately $cc$APPROX_INSTALL_MB MB$nn of space"
fi

MAX_MAKE_JOBS=${MAX_MAKE_JOBS-`nproc --all`}

echo -e "System has $cc`nproc --all`$nn cores; will use $cc$MAX_MAKE_JOBS$nn jobs"
echo Requesting root access...
sudo echo -n ""
echo Root access granted, starting...

if [ "$FRESH" == "1" ]; then
    CLEANUP=1
    unset PROTOBUF_BRANCH
    unset DPDK_VSN
    unset RTE_SDK
    unset RTE_TARGET
    unset P4C
fi

if [ "$CLEANUP" == "1" ]; then
    echo Cleaning previously downloaded files and directories
    sudo rm -rf dpdk*
    sudo rm -rf protobuf
    sudo rm -rf p4c
    sudo rm -rf t4p4s*
    sudo rm -f t4p4s_environment_variables.sh
fi

if [ ! `which curl` ] || [ ! `which git` ]; then
    echo -e "Installing ${cc}curl$nn and ${cc}git$nn"
    sudo apt-get -y install curl git
fi

# Set sensible defaults
export PARALLEL_INSTALL=${PARALLEL_INSTALL-1}
export PROTOBUF_BRANCH=${PROTOBUF_BRANCH-`git ls-remote --refs --tags https://github.com/google/protobuf | tail -1 | cut -f3 -d'/'`}

echo -e "Using ${cc}protobuf$nn branch $cc$PROTOBUF_BRANCH$nn"

# Note: currently unused, this variable can pin T4P4S bootstrap on a certain p4c commit
# P4C_COMMIT=${P4C_COMMIT-80f8970b5ec8e57c4a3611da343461b5b0a8dda3}

DPDK_VSN="19.11"
DPDK_FILEVSN="$DPDK_VSN"


if [ "$RTE_TARGET" != "" ]; then
    echo -e "Using ${cc}DPDK target$nn RTE_TARGET=$cc$RTE_TARGET$nn"
else
    DPDKCC=gcc
    which clang >/dev/null
    [ $? -eq 0 ] && DPDKCC=clang

    echo -e "DPDK will be compiled using ${cc}$DPDKCC$nn"
    export RTE_TARGET=x86_64-native-linuxapp-$DPDKCC
fi

if [ "$USE_OPTIONAL_PACKAGES" != "" ]; then
    OPT_PACKAGES="python-ipdb python-termcolor python-backtrace python-pip python-yaml python-ujson python-ruamel.yaml"
fi

T4P4S_DIR=t4p4s
[ $# -gt 0 ] && T4P4S_DIR="t4p4s-$1" && T4P4S_CLONE_OPT="$T4P4S_DIR -b $1" && echo -e "Using the $cc$1$nn branch of T4P4S"


echo

# Download libraries
sudo apt-get update && sudo apt-get -y install g++ automake libtool libgc-dev bison flex libfl-dev libgmp-dev libboost-dev libboost-iostreams-dev pkg-config python python-scapy python-ipaddr python-dill tcpdump cmake python-setuptools libprotobuf-dev libnuma-dev ccache $OPT_PACKAGES &
WAITPROC_APTGET="$!"
[ $PARALLEL_INSTALL -ne 0 ] || wait "$WAITPROC_APTGET"


# Wait for apt-get to finish
[ $PARALLEL_INSTALL -ne 1 ] || wait "$WAITPROC_APTGET"

if [ "$USE_OPTIONAL_PACKAGES" != "" ]; then
    pip install backtrace
fi


# Setup DPDK

export RTE_SDK=`pwd`/`ls -d dpdk*$DPDK_FILEVSN*/`

cd "$RTE_SDK"
make install DESTDIR=myinstall T="${RTE_TARGET}" LDFLAGS="-fuse-ld=gold" -j ${MAX_MAKE_JOBS}
cd ..


cd protobuf
./autogen.sh
./configure LD=ld.gold
make -j ${MAX_MAKE_JOBS}
sudo make install -j ${MAX_MAKE_JOBS}
sudo ldconfig
cd ..



export P4C=`pwd`/p4c

cd p4c
./bootstrap.sh
cd build
LD=ld.gold cmake ..
make -j ${MAX_MAKE_JOBS}
sudo make install -j ${MAX_MAKE_JOBS}
cd ../..



cat <<EOF >./t4p4s_environment_variables.sh
export DPDK_VSN=${DPDK_VSN}
export RTE_SDK=`pwd`/`ls -d dpdk*$DPDK_FILEVSN*/`
export RTE_TARGET=${RTE_TARGET}
export P4C=`pwd`/p4c
export T4P4S=${T4P4S_DIR}
EOF

chmod +x `pwd`/t4p4s_environment_variables.sh
. `pwd`/t4p4s_environment_variables.sh

echo Environment variable config is done
echo -e "Environment variable config is saved in ${cc}`pwd`/t4p4s_environment_variables.sh$nn"

if [[ $(grep "t4p4s_environment_variables.sh" ~/.profile) ]]; then
    echo -e "Your ${cc}~/.profile$nn is ${cc}not modified$nn, as it already calls t4p4s_environment_variables.sh"
else
    echo >> ~/.profile
    echo ". `pwd`/t4p4s_environment_variables.sh" >> ~/.profile
    echo -e "Environment variable config is ${cc}enabled on login$nn: your ${cc}~/.profile$nn will run `pwd`/t4p4s_environment_variables.sh"
fi

cd ${T4P4S_DIR}
