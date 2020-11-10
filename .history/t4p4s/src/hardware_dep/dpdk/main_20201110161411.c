/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// A large portion of the code in this file comes from
// main.c in the l3fwd example of DPDK 2.2.0.

#include "dpdk_lib.h"
#include <rte_ethdev.h>

#include "gen_include.h"
#include "dpdk_nicon.c"

#ifndef T4P4S_NIC_VARIANT
#error The NIC variant is undefined
#endif

#ifdef T4P4S_SUPPRESS_EAL
    #include <unistd.h>
    #include <stdio.h>
#endif

//TODO BY IAN
#define uint32_t_to_char(ip, a, b, c, d) do{\
    *a = (uint8_t)(ip >> 24 & 0xff);\
    *b = (uint8_t)(ip >> 16 & 0xff);\
    *c = (uint8_t)(ip >> 8 & 0xff);\
    *d = (uint8_t)(ip & 0xff);\
}while (0)

//extern lcore_data *static_lcore;
packet_descriptor_t *static_pd;
static void print_mac(uint8_t *mac){
    printf("%02x:%02x:%02x:%02x:%02x:%02x:\n",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

// TODO from...
extern void initialize_args(int argc, char **argv);
extern void initialize_nic();
extern int init_tables();
extern int init_memories();

extern int flush_tables();

extern int launch_count();
extern void t4p4s_abnormal_exit(int retval, int idx);
extern void t4p4s_pre_launch(int idx);
extern void t4p4s_post_launch(int idx);
extern int t4p4s_normal_exit();

// TODO from...
extern void init_control_plane();

// defined in the generated file dataplane.c
extern void handle_packet(packet_descriptor_t* pd, lookup_table_t** tables, parser_state_t* pstate, uint32_t portid);

// defined separately for each example
extern bool core_is_working(struct lcore_data* lcdata);
extern bool receive_packet(packet_descriptor_t* pd, struct lcore_data* lcdata, unsigned pkt_idx);
extern void free_packet(packet_descriptor_t* pd);
extern bool is_packet_handled(packet_descriptor_t* pd, struct lcore_data* lcdata);
extern void init_storage();
extern void main_loop_pre_rx(struct lcore_data* lcdata);
extern void main_loop_post_rx(struct lcore_data* lcdata);
extern void main_loop_post_single_rx(struct lcore_data* lcdata, bool got_packet);
extern uint32_t get_portid(struct lcore_data* lcdata, unsigned queue_idx);
extern void main_loop_rx_group(struct lcore_data* lcdata, unsigned queue_idx);
extern unsigned get_pkt_count_in_group(struct lcore_data* lcdata);
extern unsigned get_queue_count(struct lcore_data* lcdata);
extern void send_single_packet(struct lcore_data* lcdata, packet_descriptor_t* pd, packet* pkt, int egress_port, int ingress_port);
extern void send_broadcast_packet(struct lcore_data* lcdata, packet_descriptor_t* pd, int egress_port, int ingress_port);
extern struct lcore_data init_lcore_data();
extern packet* clone_packet(packet* pd, struct rte_mempool* mempool);
extern void init_parser_state(parser_state_t*);

//=============================================================================

extern uint32_t get_port_mask();
extern uint8_t get_port_count();

void get_broadcast_port_msg(char result[256], int ingress_port) {
    uint8_t nb_ports = get_port_count();
    uint32_t port_mask = get_port_mask();

    char* result_ptr = result;
    bool is_first_printed_port = true;
    for (uint8_t portidx = 0; portidx < RTE_MAX_ETHPORTS; ++portidx) {
        if (portidx == ingress_port) {
           continue;
        }

        bool is_port_disabled = (port_mask & (1 << portidx)) == 0;
        if (is_port_disabled)   continue;

        int printed_bytes = sprintf(result_ptr, "%s" T4LIT(%d,port), is_first_printed_port ? "" : ", ", portidx);
        result_ptr += printed_bytes;
        is_first_printed_port = false;
    }
}


void broadcast_packet(struct lcore_data* lcdata, packet_descriptor_t* pd, int egress_port, int ingress_port)
{
    uint8_t nb_ports = get_port_count();
    uint32_t port_mask = get_port_mask();

    uint8_t nb_port = 0;
    for (uint8_t portidx = 0; nb_port < nb_ports - 1 && portidx < RTE_MAX_ETHPORTS; ++portidx) {
        if (portidx == ingress_port) {
           continue;
        }

        bool is_port_disabled = (port_mask & (1 << portidx)) == 0;
        if (is_port_disabled)   continue;

        packet* pkt_out = (nb_port < nb_ports) ? clone_packet(pd->wrapper, lcdata->mempool) : pd->wrapper;
        send_single_packet(lcdata, pd, pkt_out, portidx, ingress_port);

        nb_port++;
    }

    if (unlikely(nb_port != nb_ports - 1)) {
        debug(" " T4LIT(!!!!,error) " " T4LIT(Wrong port count,error) ": " T4LIT(%d) " ports should be present, but only " T4LIT(%d) " found\n", nb_ports, nb_port);
    }
}

/* Enqueue a single packet, and send burst if queue is filled */
// void send_packet(struct lcore_data* lcdata, packet_descriptor_t* pd, int egress_port, int ingress_port)
// {
//     uint32_t lcore_id = rte_lcore_id();
//     struct rte_mbuf* mbuf = (struct rte_mbuf *)pd->wrapper;

//     if (unlikely(egress_port == T4P4S_BROADCAST_PORT)) {
//         #ifdef T4P4S_DEBUG
//             char ports_msg[256];
//             get_broadcast_port_msg(ports_msg, ingress_port);
//             dbg_bytes(rte_pktmbuf_mtod(mbuf, uint8_t*), rte_pktmbuf_pkt_len(mbuf), "   " T4LIT(<<,outgoing) " " T4LIT(Broadcasting,outgoing) " packet from port " T4LIT(%d,port) " to all other ports (%s) (" T4LIT(%d) " bytes): ", ingress_port, ports_msg, rte_pktmbuf_pkt_len(mbuf));
//         #endif
//         broadcast_packet(lcdata, pd, egress_port, ingress_port);
//     } else {
//         dbg_bytes(rte_pktmbuf_mtod(mbuf, uint8_t*), rte_pktmbuf_pkt_len(mbuf), "   " T4LIT(<<,outgoing) " " T4LIT(Emitting,outgoing) " packet on port " T4LIT(%d,port) " (" T4LIT(%d) " bytes): ", egress_port, rte_pktmbuf_pkt_len(mbuf));
//         send_single_packet(lcdata, pd, pd->wrapper, egress_port, ingress_port);
//     }
// }
void send_packet(struct lcore_data* lcdata, packet_descriptor_t* pd, int egress_port, int ingress_port)
{
    uint32_t lcore_id = rte_lcore_id();
    struct rte_mbuf* mbuf = (struct rte_mbuf *)pd->wrapper;

    if (unlikely(egress_port == T4P4S_BROADCAST_PORT)) {
        #ifdef T4P4S_DEBUG
            char ports_msg[256];
            get_broadcast_port_msg(ports_msg, ingress_port);
            dbg_bytes(rte_pktmbuf_mtod(mbuf, uint8_t*), rte_pktmbuf_pkt_len(mbuf), "   " T4LIT(<<,outgoing) " " T4LIT(Broadcasting,outgoing) " packet from port " T4LIT(%d,port) " to all other ports (%s) (" T4LIT(%d) " bytes): ", ingress_port, ports_msg, rte_pktmbuf_pkt_len(mbuf));
        #endif
        broadcast_packet(lcdata, pd, egress_port, ingress_port);
    } else if (unlikely(egress_port == T4P4S_PACKET_IN))
    {
        // //rte_pktmbuf_mtod得到data的首地址
        // //TODO BY IAN capture packets
        // struct rte_ether_hdr *eth_hdr;
        // struct rte_ipv4_hdr *ipv4_hdr;
        // unsigned short a, b, c, d;

        // //预存命令，预先存到缓存中，防止缓存不命中
        // //rte_prefetch0(rte_pktmbuf_mtod(mbuf, void *));
        // eth_hdr = rte_pktmbuf_mtod(mbuf,struct rte_ether_hdr *);
        // printf("src mac:\n");
        // print_mac(eth_hdr->s_addr.addr_bytes);
        // printf("dst mac:\n");
        // print_mac(eth_hdr->d_addr.addr_bytes);

        // ipv4_hdr = rte_pktmbuf_mtod_offset(mbuf, struct rte_ipv4_hdr *,
        //         sizeof(struct rte_ether_hdr));
        // uint32_t_to_char(rte_bswap32(ipv4_hdr->src_addr), &a, &b, &c, &d);
        // printf("Packet Src:%hhu.%hhu.%hhu.%hhu \n", a, b, c, d);
        // uint32_t_to_char(rte_bswap32(ipv4_hdr->dst_addr), &a, &b, &c, &d);
        // printf("Dst:%hhu.%hhu.%hhu.%hhu \n", a, b, c, d);

        // printf("Src port:%hu,Dst port:%hu \n",
        //             rte_bswap16(*(uint16_t *)(ipv4_hdr + 1)),
        //             rte_bswap16(*((uint16_t *)(ipv4_hdr + 1) + 1)));
        // printf("total length: %d\n",ipv4_hdr->total_length);
        // auto eth_type = rte_bswap16(eth_hdr->ether_type);
        // printf("eth_type: %d\n",eth_type);
        // printf("===========================================================\n");
        printf("egress_port == T4P4S_PACKET_IN");
        send_burst_to_controller(eth_hdr);    

    } else {
        dbg_bytes(rte_pktmbuf_mtod(mbuf, uint8_t*), rte_pktmbuf_pkt_len(mbuf), "   " T4LIT(<<,outgoing) " " T4LIT(Emitting,outgoing) " packet on port " T4LIT(%d,port) " (" T4LIT(%d) " bytes): ", egress_port, rte_pktmbuf_pkt_len(mbuf));
        send_single_packet(lcdata, pd, pd->wrapper, egress_port, ingress_port);
    }
}

void do_single_tx(struct lcore_data* lcdata, packet_descriptor_t* pd, unsigned queue_idx, unsigned pkt_idx)
{
    if (unlikely(GET_INT32_AUTO_PACKET(pd, header_instance_all_metadatas, field_standard_metadata_t_drop))) {
        debug(" " T4LIT(XXXX,status) " " T4LIT(Dropping,status) " packet\n");
        free_packet(pd);
    } else {
        debug(" " T4LIT(<<<<,outgoing) " " T4LIT(Egressing,outgoing) " packet\n");

        int egress_port = extract_egress_port(pd);
        int ingress_port = extract_ingress_port(pd);

        send_packet(lcdata, pd, egress_port, ingress_port);
    }
}

void do_single_rx(struct lcore_data* lcdata, packet_descriptor_t* pd, unsigned queue_idx, unsigned pkt_idx)
{
    bool got_packet = receive_packet(pd, lcdata, pkt_idx);

    if (got_packet) {
	    if (likely(is_packet_handled(pd, lcdata))) {
	        init_parser_state(&(lcdata->conf->state.parser_state));
            //pd获取数据包pd->data = rte_pktmbuf_mtod(p, uint8_t *);
            //pd->wrapper = p;报文内容
            //数据包与流表进行比较？
            //parser_packet process_packet emit_packet
            handle_packet(pd, lcdata->conf->state.tables, &(lcdata->conf->state.parser_state), get_portid(lcdata, queue_idx));
            do_single_tx(lcdata, pd, queue_idx, pkt_idx);
        }
    }
    // int egress_port = extract_egress_port(pd);
    // if (unlikely(egress_port == T4P4S_PACKET_IN)) {
    //     //pd->data = rte_pktmbuf_mtod(p, uint8_t *);
    //     //pd->wrapper = p;容
    //     payload = pd->wrapper;
    // }
    //没啥用
    main_loop_post_single_rx(lcdata, got_packet);
}

// void do_rx(struct lcore_data* lcdata, packet_descriptor_t* pd)
// {
//     unsigned queue_count = get_queue_count(lcdata);
//     for (unsigned queue_idx = 0; queue_idx < queue_count; queue_idx++) {
//         main_loop_rx_group(lcdata, queue_idx);

//         unsigned pkt_count = get_pkt_count_in_group(lcdata);
//         for (unsigned pkt_idx = 0; pkt_idx < pkt_count; pkt_idx++) {
//             do_single_rx(lcdata, pd, queue_idx, pkt_idx);
//         }
//     }
// }
void do_rx(struct lcore_data* lcdata, packet_descriptor_t* pd)
{
    unsigned queue_count = get_queue_count(lcdata);
    for (unsigned queue_idx = 0; queue_idx < queue_count; queue_idx++) {
        
        //lcdata->nb_rx = rte_eth_rx_burst((uint8_t) get_portid(lcdata, queue_idx)端口, queue_id队列, lcdata->pkts_burst缓冲区, MAX_PKT_BURST队列大小);最多收取MAX_PKT_BURST个报文
        //接收到nb_rx个包
        //根据队列id收包确定网口队列的收包数量，nb_rx赋值
        main_loop_rx_group(lcdata, queue_idx);
        
        //pkt_count = nb_rx
        unsigned pkt_count = get_pkt_count_in_group(lcdata);
        for (unsigned pkt_idx = 0; pkt_idx < pkt_count; pkt_idx++) {
            do_single_rx(lcdata, pd, queue_idx, pkt_idx);
        }
    }
}

//每个core上循环的函数
bool dpdk_main_loop()
{
    struct lcore_data lcdata = init_lcore_data();
    if (!lcdata.is_valid) {
    	debug("lcore data is invalid, exiting\n");
    	return false;
    }

    packet_descriptor_t pd;
    init_dataplane(&pd, lcdata.conf->state.tables);

    //static_lcore = &lcdata;
    static_pd = &pd;

    while (core_is_working(&lcdata)) {
        //计算发送时间
        main_loop_pre_rx(&lcdata);

        do_rx(&lcdata, &pd);
        //没啥用
        main_loop_post_rx(&lcdata);
    }

    return lcdata.is_valid;
}


static int
launch_one_lcore(__attribute__((unused)) void *dummy)
{
    bool success = dpdk_main_loop();
    return success ? 0 : -1;
}

int launch_dpdk()
{
    rte_eal_mp_remote_launch(launch_one_lcore, NULL, CALL_MASTER);

    unsigned lcore_id;
    RTE_LCORE_FOREACH_SLAVE(lcore_id) {
        if (rte_eal_wait_lcore(lcore_id) < 0)
            return -1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    debug("Init switch\n");

/*
    rte_eal_init(argc, argv);
    parse_args(argc, argv);
    初始化eal和参数
    */
    initialize_args(argc, argv);
    /*
    dpdk_init_nic()：
    包括：
    init_lcore_rx_queues();检查 rx 队列数是否过多，把 param 的东西放到 conf 里，初始化rx队列
    get_nb_ports();获得网口数量
    nb_lcores = rte_lcore_count();获得lcore 数量
    reset_mbuf_pools();重置mbuf池，DMA报文存取地址
    init_mbuf_pool(socketid);对每个lcore进行初始化mbuf
    dpdk_init_port(nb_ports, nb_lcores, portid);初始化port -->执行：rte_eth_dev_configure(portid, nb_rx_queue,(uint16_t)n_tx_queue, &port_conf); 
                                                --> init_tx_on_lcore(lcore_id, portid, queueid)申请并设置一个发包队列 -->rte_eth_tx_queue_setup(portid, queueid, t4p4s_nb_txd, socketid, txconf);
    dpdk_init_lcore(lcore_id);初始化lcore ->执行：dpdk_init_rx_queue(queue, lcore_id, qconf);-> 
                                rte_eth_rx_queue_setup(portid, queueid, t4p4s_nb_rxd, socketid, NULL, pktmbuf_pool[socketid]);申请并设置一个收包队列
    对每个端口开始port：
    rte_eth_dev_start(portid);开始device,启动网卡
    rte_eth_promiscuous_enable(portid);开启混杂模式


    nb_ports网口总数
    nb_rx某个网口的某个队列的缓冲区中收包数量，或者叫队列大小
    rx_rings、tx_rings网口队列的个数
    */
    initialize_nic();

    int launch_count2 = launch_count();
    for (int i = 0; i < launch_count2; ++i) {
        debug("Init execution\n");

        init_tables();

          //内存池初始化rte_pktmbuf_pool_create-->pktmbuf_pool[0]报文存储池
        init_storage();

        //没啥用
        init_memories();
        debug(" " T4LIT(::::,incoming) " Init control plane connection\n");
        /*
        create_backend(3, 1000, "localhost", 11111, recv_from_controller);
        launch_backend(bg);
        */
        init_control_plane();

        t4p4s_pre_launch(i);

        /* launch per-lcore init on every lcore */
        int retval = launch_dpdk();
        if (retval < 0) {
            t4p4s_abnormal_exit(retval, i);
            return retval;
        }

        t4p4s_post_launch(i);

        flush_tables();
    }

    return t4p4s_normal_exit();
}
