#ifndef __RTE_CONFIG_H
#define __RTE_CONFIG_H
#undef RTE_VER_PREFIX
#define RTE_VER_PREFIX "DPDK"
#undef RTE_VER_YEAR
#define RTE_VER_YEAR 19
#undef RTE_VER_MONTH
#define RTE_VER_MONTH 11
#undef RTE_VER_MINOR
#define RTE_VER_MINOR 2
#undef RTE_VER_SUFFIX
#define RTE_VER_SUFFIX ""
#undef RTE_VER_RELEASE
#define RTE_VER_RELEASE 99
#undef RTE_EXEC_ENV
#define RTE_EXEC_ENV "linuxapp"
#undef RTE_ARCH
#define RTE_ARCH "x86_64"
#undef RTE_MACHINE
#define RTE_MACHINE "native"
#undef RTE_TOOLCHAIN
#define RTE_TOOLCHAIN "gcc"
#undef RTE_FORCE_INTRINSICS
#undef RTE_ARCH_STRICT_ALIGN
#undef RTE_ENABLE_LTO
#undef RTE_BUILD_SHARED_LIB
#undef RTE_NEXT_ABI
#define RTE_NEXT_ABI 1
#undef RTE_CACHE_LINE_SIZE
#define RTE_CACHE_LINE_SIZE 64
#undef RTE_USE_C11_MEM_MODEL
#undef RTE_LIBRTE_EAL
#define RTE_LIBRTE_EAL 1
#undef RTE_MAX_LCORE
#define RTE_MAX_LCORE 128
#undef RTE_MAX_NUMA_NODES
#define RTE_MAX_NUMA_NODES 8
#undef RTE_MAX_HEAPS
#define RTE_MAX_HEAPS 32
#undef RTE_MAX_MEMSEG_LISTS
#define RTE_MAX_MEMSEG_LISTS 64
#undef RTE_MAX_MEMSEG_PER_LIST
#define RTE_MAX_MEMSEG_PER_LIST 8192
#undef RTE_MAX_MEM_MB_PER_LIST
#define RTE_MAX_MEM_MB_PER_LIST 32768
#undef RTE_MAX_MEMSEG_PER_TYPE
#define RTE_MAX_MEMSEG_PER_TYPE 32768
#undef RTE_MAX_MEM_MB_PER_TYPE
#define RTE_MAX_MEM_MB_PER_TYPE 131072
#undef RTE_MAX_MEM_MB
#define RTE_MAX_MEM_MB 524288
#undef RTE_MAX_MEMZONE
#define RTE_MAX_MEMZONE 2560
#undef RTE_MAX_TAILQ
#define RTE_MAX_TAILQ 32
#undef RTE_ENABLE_ASSERT
#undef RTE_LOG_DP_LEVEL
#define RTE_LOG_DP_LEVEL RTE_LOG_INFO
#undef RTE_LOG_HISTORY
#define RTE_LOG_HISTORY 256
#undef RTE_BACKTRACE
#define RTE_BACKTRACE 1
#undef RTE_LIBEAL_USE_HPET
#undef RTE_EAL_ALWAYS_PANIC_ON_ERROR
#undef RTE_EAL_IGB_UIO
#define RTE_EAL_IGB_UIO 1
#undef RTE_EAL_VFIO
#define RTE_EAL_VFIO 1
#undef RTE_MAX_VFIO_GROUPS
#define RTE_MAX_VFIO_GROUPS 64
#undef RTE_MAX_VFIO_CONTAINERS
#define RTE_MAX_VFIO_CONTAINERS 64
#undef RTE_MALLOC_DEBUG
#undef RTE_EAL_NUMA_AWARE_HUGEPAGES
#define RTE_EAL_NUMA_AWARE_HUGEPAGES 1
#undef RTE_USE_LIBBSD
#undef RTE_ENABLE_AVX
#define RTE_ENABLE_AVX 1
#undef RTE_ENABLE_AVX512
#undef RTE_ARM_FEATURE_ATOMICS
#undef RTE_EAL_PMD_PATH
#define RTE_EAL_PMD_PATH ""
#undef RTE_LIBRTE_EAL_VMWARE_TSC_MAP_SUPPORT
#define RTE_LIBRTE_EAL_VMWARE_TSC_MAP_SUPPORT 1
#undef RTE_LIBRTE_PCI
#define RTE_LIBRTE_PCI 1
#undef RTE_LIBRTE_KVARGS
#define RTE_LIBRTE_KVARGS 1
#undef RTE_LIBRTE_ETHER
#define RTE_LIBRTE_ETHER 1
#undef RTE_LIBRTE_ETHDEV_DEBUG
#undef RTE_MAX_ETHPORTS
#define RTE_MAX_ETHPORTS 32
#undef RTE_MAX_QUEUES_PER_PORT
#define RTE_MAX_QUEUES_PER_PORT 1024
#undef RTE_LIBRTE_IEEE1588
#undef RTE_ETHDEV_QUEUE_STAT_CNTRS
#define RTE_ETHDEV_QUEUE_STAT_CNTRS 16
#undef RTE_ETHDEV_RXTX_CALLBACKS
#define RTE_ETHDEV_RXTX_CALLBACKS 1
#undef RTE_ETHDEV_PROFILE_WITH_VTUNE
#undef RTE_ETHDEV_TX_PREPARE_NOOP
#undef RTE_LIBRTE_COMMON_DPAAX
#define RTE_LIBRTE_COMMON_DPAAX 1
#undef RTE_LIBRTE_IFPGA_BUS
#define RTE_LIBRTE_IFPGA_BUS 1
#undef RTE_LIBRTE_PCI_BUS
#define RTE_LIBRTE_PCI_BUS 1
#undef RTE_LIBRTE_VDEV_BUS
#define RTE_LIBRTE_VDEV_BUS 1
#undef RTE_LIBRTE_ARK_PMD
#define RTE_LIBRTE_ARK_PMD 1
#undef RTE_LIBRTE_ARK_PAD_TX
#define RTE_LIBRTE_ARK_PAD_TX 1
#undef RTE_LIBRTE_ARK_DEBUG_RX
#undef RTE_LIBRTE_ARK_DEBUG_TX
#undef RTE_LIBRTE_ARK_DEBUG_STATS
#undef RTE_LIBRTE_ARK_DEBUG_TRACE
#undef RTE_LIBRTE_ATLANTIC_PMD
#define RTE_LIBRTE_ATLANTIC_PMD 1
#undef RTE_LIBRTE_AXGBE_PMD
#define RTE_LIBRTE_AXGBE_PMD 1
#undef RTE_LIBRTE_AXGBE_PMD_DEBUG
#undef RTE_LIBRTE_BNX2X_PMD
#undef RTE_LIBRTE_BNX2X_DEBUG_RX
#undef RTE_LIBRTE_BNX2X_DEBUG_TX
#undef RTE_LIBRTE_BNX2X_MF_SUPPORT
#undef RTE_LIBRTE_BNX2X_DEBUG_PERIODIC
#undef RTE_LIBRTE_BNXT_PMD
#define RTE_LIBRTE_BNXT_PMD 1
#undef RTE_LIBRTE_CXGBE_PMD
#define RTE_LIBRTE_CXGBE_PMD 1
#undef RTE_LIBRTE_PFE_PMD
#undef RTE_LIBRTE_DPAA_BUS
#define RTE_LIBRTE_DPAA_BUS 1
#undef RTE_LIBRTE_DPAA_MEMPOOL
#define RTE_LIBRTE_DPAA_MEMPOOL 1
#undef RTE_LIBRTE_DPAA_PMD
#define RTE_LIBRTE_DPAA_PMD 1
#undef RTE_LIBRTE_DPAA_HWDEBUG
#undef RTE_LIBRTE_FSLMC_BUS
#define RTE_LIBRTE_FSLMC_BUS 1
#undef RTE_LIBRTE_DPAA2_MEMPOOL
#define RTE_LIBRTE_DPAA2_MEMPOOL 1
#undef RTE_LIBRTE_DPAA2_USE_PHYS_IOVA
#define RTE_LIBRTE_DPAA2_USE_PHYS_IOVA 1
#undef RTE_LIBRTE_DPAA2_PMD
#define RTE_LIBRTE_DPAA2_PMD 1
#undef RTE_LIBRTE_DPAA2_DEBUG_DRIVER
#undef RTE_LIBRTE_ENETC_PMD
#define RTE_LIBRTE_ENETC_PMD 1
#undef RTE_LIBRTE_ENA_PMD
#define RTE_LIBRTE_ENA_PMD 1
#undef RTE_LIBRTE_ENA_DEBUG_RX
#undef RTE_LIBRTE_ENA_DEBUG_TX
#undef RTE_LIBRTE_ENA_DEBUG_TX_FREE
#undef RTE_LIBRTE_ENA_COM_DEBUG
#undef RTE_LIBRTE_ENIC_PMD
#define RTE_LIBRTE_ENIC_PMD 1
#undef RTE_LIBRTE_EM_PMD
#define RTE_LIBRTE_EM_PMD 1
#undef RTE_LIBRTE_IGB_PMD
#define RTE_LIBRTE_IGB_PMD 1
#undef RTE_LIBRTE_E1000_DEBUG_RX
#undef RTE_LIBRTE_E1000_DEBUG_TX
#undef RTE_LIBRTE_E1000_DEBUG_TX_FREE
#undef RTE_LIBRTE_E1000_PF_DISABLE_STRIP_CRC
#undef RTE_LIBRTE_HINIC_PMD
#define RTE_LIBRTE_HINIC_PMD 1
#undef RTE_LIBRTE_HNS3_PMD
#define RTE_LIBRTE_HNS3_PMD 1
#undef RTE_LIBRTE_IXGBE_PMD
#define RTE_LIBRTE_IXGBE_PMD 1
#undef RTE_LIBRTE_IXGBE_DEBUG_RX
#undef RTE_LIBRTE_IXGBE_DEBUG_TX
#undef RTE_LIBRTE_IXGBE_DEBUG_TX_FREE
#undef RTE_LIBRTE_IXGBE_PF_DISABLE_STRIP_CRC
#undef RTE_IXGBE_INC_VECTOR
#define RTE_IXGBE_INC_VECTOR 1
#undef RTE_LIBRTE_IXGBE_BYPASS
#undef RTE_LIBRTE_I40E_PMD
#define RTE_LIBRTE_I40E_PMD 1
#undef RTE_LIBRTE_I40E_DEBUG_RX
#undef RTE_LIBRTE_I40E_DEBUG_TX
#undef RTE_LIBRTE_I40E_DEBUG_TX_FREE
#undef RTE_LIBRTE_I40E_RX_ALLOW_BULK_ALLOC
#define RTE_LIBRTE_I40E_RX_ALLOW_BULK_ALLOC 1
#undef RTE_LIBRTE_I40E_INC_VECTOR
#define RTE_LIBRTE_I40E_INC_VECTOR 1
#undef RTE_LIBRTE_I40E_16BYTE_RX_DESC
#undef RTE_LIBRTE_I40E_QUEUE_NUM_PER_PF
#define RTE_LIBRTE_I40E_QUEUE_NUM_PER_PF 64
#undef RTE_LIBRTE_I40E_QUEUE_NUM_PER_VM
#define RTE_LIBRTE_I40E_QUEUE_NUM_PER_VM 4
#undef RTE_LIBRTE_FM10K_PMD
#define RTE_LIBRTE_FM10K_PMD 1
#undef RTE_LIBRTE_FM10K_DEBUG_RX
#undef RTE_LIBRTE_FM10K_DEBUG_TX
#undef RTE_LIBRTE_FM10K_DEBUG_TX_FREE
#undef RTE_LIBRTE_FM10K_RX_OLFLAGS_ENABLE
#define RTE_LIBRTE_FM10K_RX_OLFLAGS_ENABLE 1
#undef RTE_LIBRTE_FM10K_INC_VECTOR
#define RTE_LIBRTE_FM10K_INC_VECTOR 1
#undef RTE_LIBRTE_ICE_PMD
#define RTE_LIBRTE_ICE_PMD 1
#undef RTE_LIBRTE_ICE_DEBUG_RX
#undef RTE_LIBRTE_ICE_DEBUG_TX
#undef RTE_LIBRTE_ICE_DEBUG_TX_FREE
#undef RTE_LIBRTE_ICE_RX_ALLOW_BULK_ALLOC
#define RTE_LIBRTE_ICE_RX_ALLOW_BULK_ALLOC 1
#undef RTE_LIBRTE_ICE_16BYTE_RX_DESC
#undef RTE_LIBRTE_IAVF_PMD
#define RTE_LIBRTE_IAVF_PMD 1
#undef RTE_LIBRTE_IAVF_DEBUG_TX
#undef RTE_LIBRTE_IAVF_DEBUG_TX_FREE
#undef RTE_LIBRTE_IAVF_DEBUG_RX
#undef RTE_LIBRTE_IAVF_DEBUG_DUMP_DESC
#undef RTE_LIBRTE_IAVF_16BYTE_RX_DESC
#undef RTE_LIBRTE_IPN3KE_PMD
#undef RTE_LIBRTE_MLX4_PMD
#undef RTE_LIBRTE_MLX4_DEBUG
#undef RTE_LIBRTE_MLX5_PMD
#undef RTE_LIBRTE_MLX5_DEBUG
#undef RTE_IBVERBS_LINK_DLOPEN
#undef RTE_IBVERBS_LINK_STATIC
#undef RTE_LIBRTE_NFP_PMD
#define RTE_LIBRTE_NFP_PMD 1
#undef RTE_LIBRTE_NFP_DEBUG_TX
#undef RTE_LIBRTE_NFP_DEBUG_RX
#undef RTE_LIBRTE_QEDE_PMD
#define RTE_LIBRTE_QEDE_PMD 1
#undef RTE_LIBRTE_QEDE_DEBUG_TX
#undef RTE_LIBRTE_QEDE_DEBUG_RX
#undef RTE_LIBRTE_QEDE_FW
#define RTE_LIBRTE_QEDE_FW ""
#undef RTE_LIBRTE_SFC_EFX_PMD
#define RTE_LIBRTE_SFC_EFX_PMD 1
#undef RTE_LIBRTE_SFC_EFX_DEBUG
#undef RTE_LIBRTE_PMD_SZEDATA2
#undef RTE_LIBRTE_NFB_PMD
#undef RTE_LIBRTE_THUNDERX_NICVF_PMD
#define RTE_LIBRTE_THUNDERX_NICVF_PMD 1
#undef RTE_LIBRTE_THUNDERX_NICVF_DEBUG_RX
#undef RTE_LIBRTE_THUNDERX_NICVF_DEBUG_TX
#undef RTE_LIBRTE_LIO_PMD
#define RTE_LIBRTE_LIO_PMD 1
#undef RTE_LIBRTE_LIO_DEBUG_RX
#undef RTE_LIBRTE_LIO_DEBUG_TX
#undef RTE_LIBRTE_LIO_DEBUG_MBOX
#undef RTE_LIBRTE_LIO_DEBUG_REGS
#undef RTE_LIBRTE_OCTEONTX_PMD
#define RTE_LIBRTE_OCTEONTX_PMD 1
#undef RTE_LIBRTE_OCTEONTX2_PMD
#define RTE_LIBRTE_OCTEONTX2_PMD 1
#undef RTE_LIBRTE_AVP_PMD
#define RTE_LIBRTE_AVP_PMD 1
#undef RTE_LIBRTE_AVP_DEBUG_RX
#undef RTE_LIBRTE_AVP_DEBUG_TX
#undef RTE_LIBRTE_AVP_DEBUG_BUFFERS
#undef RTE_LIBRTE_VIRTIO_PMD
#define RTE_LIBRTE_VIRTIO_PMD 1
#undef RTE_LIBRTE_VIRTIO_DEBUG_RX
#undef RTE_LIBRTE_VIRTIO_DEBUG_TX
#undef RTE_LIBRTE_VIRTIO_DEBUG_DUMP
#undef RTE_VIRTIO_USER
#define RTE_VIRTIO_USER 1
#undef RTE_LIBRTE_VMXNET3_PMD
#define RTE_LIBRTE_VMXNET3_PMD 1
#undef RTE_LIBRTE_VMXNET3_DEBUG_RX
#undef RTE_LIBRTE_VMXNET3_DEBUG_TX
#undef RTE_LIBRTE_VMXNET3_DEBUG_TX_FREE
#undef RTE_LIBRTE_PMD_AF_PACKET
#define RTE_LIBRTE_PMD_AF_PACKET 1
#undef RTE_LIBRTE_PMD_AF_XDP
#undef RTE_LIBRTE_PMD_MEMIF
#define RTE_LIBRTE_PMD_MEMIF 1
#undef RTE_LIBRTE_PMD_BOND
#define RTE_LIBRTE_PMD_BOND 1
#undef RTE_LIBRTE_BOND_DEBUG_ALB
#undef RTE_LIBRTE_BOND_DEBUG_ALB_L1
#undef RTE_LIBRTE_PMD_FAILSAFE
#define RTE_LIBRTE_PMD_FAILSAFE 1
#undef RTE_LIBRTE_MVPP2_PMD
#undef RTE_LIBRTE_MVNETA_PMD
#undef RTE_LIBRTE_VMBUS
#define RTE_LIBRTE_VMBUS 1
#undef RTE_LIBRTE_NETVSC_PMD
#define RTE_LIBRTE_NETVSC_PMD 1
#undef RTE_LIBRTE_NETVSC_DEBUG_RX
#undef RTE_LIBRTE_NETVSC_DEBUG_TX
#undef RTE_LIBRTE_NETVSC_DEBUG_DUMP
#undef RTE_LIBRTE_VDEV_NETVSC_PMD
#define RTE_LIBRTE_VDEV_NETVSC_PMD 1
#undef RTE_LIBRTE_PMD_NULL
#define RTE_LIBRTE_PMD_NULL 1
#undef RTE_LIBRTE_PMD_PCAP
#undef RTE_LIBRTE_PMD_RING
#define RTE_LIBRTE_PMD_RING 1
#undef RTE_PMD_RING_MAX_RX_RINGS
#define RTE_PMD_RING_MAX_RX_RINGS 16
#undef RTE_PMD_RING_MAX_TX_RINGS
#define RTE_PMD_RING_MAX_TX_RINGS 16
#undef RTE_LIBRTE_PMD_SOFTNIC
#define RTE_LIBRTE_PMD_SOFTNIC 1
#undef RTE_LIBRTE_PMD_TAP
#define RTE_LIBRTE_PMD_TAP 1
#undef RTE_PMD_PACKET_PREFETCH
#define RTE_PMD_PACKET_PREFETCH 1
#undef RTE_LIBRTE_BBDEV
#define RTE_LIBRTE_BBDEV 1
#undef RTE_LIBRTE_BBDEV_DEBUG
#undef RTE_BBDEV_MAX_DEVS
#define RTE_BBDEV_MAX_DEVS 128
#undef RTE_BBDEV_OFFLOAD_COST
#define RTE_BBDEV_OFFLOAD_COST 1
#undef RTE_BBDEV_SDK_AVX2
#undef RTE_BBDEV_SDK_AVX512
#undef RTE_LIBRTE_PMD_BBDEV_NULL
#define RTE_LIBRTE_PMD_BBDEV_NULL 1
#undef RTE_LIBRTE_PMD_BBDEV_TURBO_SW
#define RTE_LIBRTE_PMD_BBDEV_TURBO_SW 1
#undef RTE_LIBRTE_PMD_BBDEV_FPGA_LTE_FEC
#define RTE_LIBRTE_PMD_BBDEV_FPGA_LTE_FEC 1
#undef RTE_LIBRTE_CRYPTODEV
#define RTE_LIBRTE_CRYPTODEV 1
#undef RTE_CRYPTO_MAX_DEVS
#define RTE_CRYPTO_MAX_DEVS 64
#undef RTE_LIBRTE_PMD_ARMV8_CRYPTO
#undef RTE_LIBRTE_PMD_ARMV8_CRYPTO_DEBUG
#undef RTE_LIBRTE_PMD_CAAM_JR
#define RTE_LIBRTE_PMD_CAAM_JR 1
#undef RTE_LIBRTE_PMD_CAAM_JR_BE
#undef RTE_LIBRTE_PMD_DPAA2_SEC
#define RTE_LIBRTE_PMD_DPAA2_SEC 1
#undef RTE_LIBRTE_PMD_DPAA_SEC
#define RTE_LIBRTE_PMD_DPAA_SEC 1
#undef RTE_LIBRTE_DPAA_MAX_CRYPTODEV
#define RTE_LIBRTE_DPAA_MAX_CRYPTODEV 4
#undef RTE_LIBRTE_PMD_OCTEONTX_CRYPTO
#define RTE_LIBRTE_PMD_OCTEONTX_CRYPTO 1
#undef RTE_LIBRTE_PMD_OCTEONTX2_CRYPTO
#define RTE_LIBRTE_PMD_OCTEONTX2_CRYPTO 1
#undef RTE_LIBRTE_PMD_QAT
#define RTE_LIBRTE_PMD_QAT 1
#undef RTE_LIBRTE_PMD_QAT_SYM
#undef RTE_LIBRTE_PMD_QAT_ASYM
#undef RTE_PMD_QAT_MAX_PCI_DEVICES
#define RTE_PMD_QAT_MAX_PCI_DEVICES 48
#undef RTE_PMD_QAT_COMP_IM_BUFFER_SIZE
#define RTE_PMD_QAT_COMP_IM_BUFFER_SIZE 65536
#undef RTE_LIBRTE_PMD_VIRTIO_CRYPTO
#define RTE_LIBRTE_PMD_VIRTIO_CRYPTO 1
#undef RTE_MAX_VIRTIO_CRYPTO
#define RTE_MAX_VIRTIO_CRYPTO 32
#undef RTE_LIBRTE_PMD_AESNI_MB
#undef RTE_LIBRTE_PMD_OPENSSL
#undef RTE_LIBRTE_PMD_AESNI_GCM
#undef RTE_LIBRTE_PMD_SNOW3G
#undef RTE_LIBRTE_PMD_SNOW3G_DEBUG
#undef RTE_LIBRTE_PMD_KASUMI
#undef RTE_LIBRTE_PMD_ZUC
#undef RTE_LIBRTE_PMD_CRYPTO_SCHEDULER
#define RTE_LIBRTE_PMD_CRYPTO_SCHEDULER 1
#undef RTE_LIBRTE_PMD_NULL_CRYPTO
#define RTE_LIBRTE_PMD_NULL_CRYPTO 1
#undef RTE_LIBRTE_PMD_CCP
#undef RTE_LIBRTE_PMD_MVSAM_CRYPTO
#undef RTE_LIBRTE_PMD_NITROX
#define RTE_LIBRTE_PMD_NITROX 1
#undef RTE_LIBRTE_SECURITY
#define RTE_LIBRTE_SECURITY 1
#undef RTE_LIBRTE_COMPRESSDEV
#define RTE_LIBRTE_COMPRESSDEV 1
#undef RTE_COMPRESS_MAX_DEVS
#define RTE_COMPRESS_MAX_DEVS 64
#undef RTE_COMPRESSDEV_TEST
#undef RTE_LIBRTE_PMD_OCTEONTX_ZIPVF
#define RTE_LIBRTE_PMD_OCTEONTX_ZIPVF 1
#undef RTE_LIBRTE_PMD_ISAL
#undef RTE_LIBRTE_PMD_ZLIB
#undef RTE_LIBRTE_EVENTDEV
#define RTE_LIBRTE_EVENTDEV 1
#undef RTE_LIBRTE_EVENTDEV_DEBUG
#undef RTE_EVENT_MAX_DEVS
#define RTE_EVENT_MAX_DEVS 16
#undef RTE_EVENT_MAX_QUEUES_PER_DEV
#define RTE_EVENT_MAX_QUEUES_PER_DEV 64
#undef RTE_EVENT_TIMER_ADAPTER_NUM_MAX
#define RTE_EVENT_TIMER_ADAPTER_NUM_MAX 32
#undef RTE_EVENT_ETH_INTR_RING_SIZE
#define RTE_EVENT_ETH_INTR_RING_SIZE 1024
#undef RTE_EVENT_CRYPTO_ADAPTER_MAX_INSTANCE
#define RTE_EVENT_CRYPTO_ADAPTER_MAX_INSTANCE 32
#undef RTE_EVENT_ETH_TX_ADAPTER_MAX_INSTANCE
#define RTE_EVENT_ETH_TX_ADAPTER_MAX_INSTANCE 32
#undef RTE_LIBRTE_PMD_SKELETON_EVENTDEV
#define RTE_LIBRTE_PMD_SKELETON_EVENTDEV 1
#undef RTE_LIBRTE_PMD_SKELETON_EVENTDEV_DEBUG
#undef RTE_LIBRTE_PMD_SW_EVENTDEV
#define RTE_LIBRTE_PMD_SW_EVENTDEV 1
#undef RTE_LIBRTE_PMD_DSW_EVENTDEV
#define RTE_LIBRTE_PMD_DSW_EVENTDEV 1
#undef RTE_LIBRTE_PMD_OCTEONTX_SSOVF
#define RTE_LIBRTE_PMD_OCTEONTX_SSOVF 1
#undef RTE_LIBRTE_PMD_OCTEONTX2_EVENTDEV
#define RTE_LIBRTE_PMD_OCTEONTX2_EVENTDEV 1
#undef RTE_LIBRTE_PMD_OPDL_EVENTDEV
#define RTE_LIBRTE_PMD_OPDL_EVENTDEV 1
#undef RTE_LIBRTE_PMD_DPAA_EVENTDEV
#define RTE_LIBRTE_PMD_DPAA_EVENTDEV 1
#undef RTE_LIBRTE_PMD_DPAA2_EVENTDEV
#define RTE_LIBRTE_PMD_DPAA2_EVENTDEV 1
#undef RTE_LIBRTE_RAWDEV
#define RTE_LIBRTE_RAWDEV 1
#undef RTE_RAWDEV_MAX_DEVS
#define RTE_RAWDEV_MAX_DEVS 64
#undef RTE_LIBRTE_PMD_SKELETON_RAWDEV
#define RTE_LIBRTE_PMD_SKELETON_RAWDEV 1
#undef RTE_LIBRTE_PMD_DPAA2_CMDIF_RAWDEV
#define RTE_LIBRTE_PMD_DPAA2_CMDIF_RAWDEV 1
#undef RTE_LIBRTE_PMD_DPAA2_QDMA_RAWDEV
#define RTE_LIBRTE_PMD_DPAA2_QDMA_RAWDEV 1
#undef RTE_LIBRTE_PMD_IFPGA_RAWDEV
#undef RTE_LIBRTE_PMD_IOAT_RAWDEV
#define RTE_LIBRTE_PMD_IOAT_RAWDEV 1
#undef RTE_LIBRTE_PMD_OCTEONTX2_DMA_RAWDEV
#define RTE_LIBRTE_PMD_OCTEONTX2_DMA_RAWDEV 1
#undef RTE_LIBRTE_PMD_NTB_RAWDEV
#define RTE_LIBRTE_PMD_NTB_RAWDEV 1
#undef RTE_LIBRTE_RING
#define RTE_LIBRTE_RING 1
#undef RTE_LIBRTE_STACK
#define RTE_LIBRTE_STACK 1
#undef RTE_LIBRTE_MEMPOOL
#define RTE_LIBRTE_MEMPOOL 1
#undef RTE_MEMPOOL_CACHE_MAX_SIZE
#define RTE_MEMPOOL_CACHE_MAX_SIZE 512
#undef RTE_LIBRTE_MEMPOOL_DEBUG
#undef RTE_DRIVER_MEMPOOL_BUCKET
#define RTE_DRIVER_MEMPOOL_BUCKET 1
#undef RTE_DRIVER_MEMPOOL_BUCKET_SIZE_KB
#define RTE_DRIVER_MEMPOOL_BUCKET_SIZE_KB 64
#undef RTE_DRIVER_MEMPOOL_RING
#define RTE_DRIVER_MEMPOOL_RING 1
#undef RTE_DRIVER_MEMPOOL_STACK
#define RTE_DRIVER_MEMPOOL_STACK 1
#undef RTE_LIBRTE_OCTEONTX_MEMPOOL
#define RTE_LIBRTE_OCTEONTX_MEMPOOL 1
#undef RTE_LIBRTE_OCTEONTX2_MEMPOOL
#define RTE_LIBRTE_OCTEONTX2_MEMPOOL 1
#undef RTE_LIBRTE_MBUF
#define RTE_LIBRTE_MBUF 1
#undef RTE_LIBRTE_MBUF_DEBUG
#undef RTE_MBUF_DEFAULT_MEMPOOL_OPS
#define RTE_MBUF_DEFAULT_MEMPOOL_OPS "ring_mp_mc"
#undef RTE_MBUF_REFCNT_ATOMIC
#define RTE_MBUF_REFCNT_ATOMIC 1
#undef RTE_PKTMBUF_HEADROOM
#define RTE_PKTMBUF_HEADROOM 128
#undef RTE_LIBRTE_TIMER
#define RTE_LIBRTE_TIMER 1
#undef RTE_LIBRTE_TIMER_DEBUG
#undef RTE_LIBRTE_CFGFILE
#define RTE_LIBRTE_CFGFILE 1
#undef RTE_LIBRTE_CMDLINE
#define RTE_LIBRTE_CMDLINE 1
#undef RTE_LIBRTE_CMDLINE_DEBUG
#undef RTE_LIBRTE_HASH
#define RTE_LIBRTE_HASH 1
#undef RTE_LIBRTE_HASH_DEBUG
#undef RTE_LIBRTE_EFD
#define RTE_LIBRTE_EFD 1
#undef RTE_LIBRTE_MEMBER
#define RTE_LIBRTE_MEMBER 1
#undef RTE_LIBRTE_JOBSTATS
#define RTE_LIBRTE_JOBSTATS 1
#undef RTE_LIBRTE_METRICS
#define RTE_LIBRTE_METRICS 1
#undef RTE_LIBRTE_BITRATE
#define RTE_LIBRTE_BITRATE 1
#undef RTE_LIBRTE_LATENCY_STATS
#define RTE_LIBRTE_LATENCY_STATS 1
#undef RTE_LIBRTE_TELEMETRY
#undef RTE_LIBRTE_RCU
#define RTE_LIBRTE_RCU 1
#undef RTE_LIBRTE_RCU_DEBUG
#undef RTE_LIBRTE_RIB
#define RTE_LIBRTE_RIB 1
#undef RTE_LIBRTE_FIB
#define RTE_LIBRTE_FIB 1
#undef RTE_LIBRTE_FIB_DEBUG
#undef RTE_LIBRTE_LPM
#define RTE_LIBRTE_LPM 1
#undef RTE_LIBRTE_LPM_DEBUG
#undef RTE_LIBRTE_ACL
#define RTE_LIBRTE_ACL 1
#undef RTE_LIBRTE_ACL_DEBUG
#undef RTE_LIBRTE_POWER
#define RTE_LIBRTE_POWER 1
#undef RTE_LIBRTE_POWER_DEBUG
#undef RTE_MAX_LCORE_FREQS
#define RTE_MAX_LCORE_FREQS 64
#undef RTE_LIBRTE_NET
#define RTE_LIBRTE_NET 1
#undef RTE_LIBRTE_IP_FRAG
#define RTE_LIBRTE_IP_FRAG 1
#undef RTE_LIBRTE_IP_FRAG_DEBUG
#undef RTE_LIBRTE_IP_FRAG_MAX_FRAG
#define RTE_LIBRTE_IP_FRAG_MAX_FRAG 4
#undef RTE_LIBRTE_IP_FRAG_TBL_STAT
#undef RTE_LIBRTE_GRO
#define RTE_LIBRTE_GRO 1
#undef RTE_LIBRTE_GSO
#define RTE_LIBRTE_GSO 1
#undef RTE_LIBRTE_METER
#define RTE_LIBRTE_METER 1
#undef RTE_LIBRTE_FLOW_CLASSIFY
#define RTE_LIBRTE_FLOW_CLASSIFY 1
#undef RTE_LIBRTE_SCHED
#define RTE_LIBRTE_SCHED 1
#undef RTE_SCHED_DEBUG
#undef RTE_SCHED_RED
#undef RTE_SCHED_COLLECT_STATS
#undef RTE_SCHED_SUBPORT_TC_OV
#undef RTE_SCHED_PORT_N_GRINDERS
#define RTE_SCHED_PORT_N_GRINDERS 8
#undef RTE_SCHED_VECTOR
#undef RTE_LIBRTE_DISTRIBUTOR
#define RTE_LIBRTE_DISTRIBUTOR 1
#undef RTE_LIBRTE_REORDER
#define RTE_LIBRTE_REORDER 1
#undef RTE_LIBRTE_PORT
#define RTE_LIBRTE_PORT 1
#undef RTE_PORT_STATS_COLLECT
#undef RTE_PORT_PCAP
#undef RTE_LIBRTE_TABLE
#define RTE_LIBRTE_TABLE 1
#undef RTE_TABLE_STATS_COLLECT
#undef RTE_LIBRTE_PIPELINE
#define RTE_LIBRTE_PIPELINE 1
#undef RTE_PIPELINE_STATS_COLLECT
#undef RTE_LIBRTE_KNI
#define RTE_LIBRTE_KNI 1
#undef RTE_LIBRTE_PMD_KNI
#define RTE_LIBRTE_PMD_KNI 1
#undef RTE_KNI_KMOD
#define RTE_KNI_KMOD 1
#undef RTE_KNI_PREEMPT_DEFAULT
#define RTE_KNI_PREEMPT_DEFAULT 1
#undef RTE_LIBRTE_PDUMP
#define RTE_LIBRTE_PDUMP 1
#undef RTE_LIBRTE_VHOST
#define RTE_LIBRTE_VHOST 1
#undef RTE_LIBRTE_VHOST_NUMA
#define RTE_LIBRTE_VHOST_NUMA 1
#undef RTE_LIBRTE_VHOST_DEBUG
#undef RTE_LIBRTE_PMD_VHOST
#define RTE_LIBRTE_PMD_VHOST 1
#undef RTE_LIBRTE_IFC_PMD
#define RTE_LIBRTE_IFC_PMD 1
#undef RTE_LIBRTE_BPF
#define RTE_LIBRTE_BPF 1
#undef RTE_LIBRTE_BPF_ELF
#undef RTE_LIBRTE_IPSEC
#define RTE_LIBRTE_IPSEC 1
#undef RTE_APP_TEST
#define RTE_APP_TEST 1
#undef RTE_APP_TEST_RESOURCE_TAR
#undef RTE_PROC_INFO
#define RTE_PROC_INFO 1
#undef RTE_TEST_PMD
#define RTE_TEST_PMD 1
#undef RTE_TEST_PMD_RECORD_CORE_CYCLES
#undef RTE_TEST_PMD_RECORD_BURST_STATS
#undef RTE_TEST_BBDEV
#define RTE_TEST_BBDEV 1
#undef RTE_APP_COMPRESS_PERF
#define RTE_APP_COMPRESS_PERF 1
#undef RTE_APP_CRYPTO_PERF
#define RTE_APP_CRYPTO_PERF 1
#undef RTE_APP_EVENTDEV
#define RTE_APP_EVENTDEV 1
#undef RTE_EXEC_ENV_LINUX
#define RTE_EXEC_ENV_LINUX 1
#undef RTE_EXEC_ENV_LINUXAPP
#define RTE_EXEC_ENV_LINUXAPP 1
#undef RTE_LIBRTE_VHOST_POSTCOPY
#undef RTE_ARCH_X86_64
#define RTE_ARCH_X86_64 1
#undef RTE_ARCH_X86
#define RTE_ARCH_X86 1
#undef RTE_ARCH_64
#define RTE_ARCH_64 1
#undef RTE_TOOLCHAIN_GCC
#define RTE_TOOLCHAIN_GCC 1
#endif /* __RTE_CONFIG_H */
