#ifndef ROUTINGPROTOCOLIMPL_H
#define ROUTINGPROTOCOLIMPL_H

#include "RoutingProtocol.h"
#include "utils.h"
#include "Node.h"
#include "AlarmHandler.h"
#include <queue>



class RoutingProtocolImpl : public RoutingProtocol {
public:
    RoutingProtocolImpl(Node *n);

    ~RoutingProtocolImpl();

    void init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type);
    // As discussed in the assignment document, your RoutingProtocolImpl is
    // first initialized with the total number of ports on the router,
    // the router's ID, and the protocol type (P_DV or P_LS) that
    // should be used. See global.h for definitions of constants P_DV
    // and P_LS.

    void handle_alarm(void *data);
    // As discussed in the assignment document, when an alarm scheduled by your
    // RoutingProtoclImpl fires, your RoutingProtocolImpl's
    // handle_alarm() function will be called, with the original piece
    // of "data" memory supplied to set_alarm() provided. After you
    // handle an alarm, the memory pointed to by "data" is under your
    // ownership and you should free it if appropriate.

    void recv(unsigned short port, void *packet, unsigned short size);
    // When a packet is received, your recv() function will be called
    // with the port number on which the packet arrives from, the
    // pointer to the packet memory, and the size of the packet in
    // bytes. When you receive a packet, the packet memory is under
    // your ownership and you should free it if appropriate. When a
    // DATA packet is created at a router by the simulator, your
    // recv() function will be called for such DATA packet, but with a
    // special port number of SPECIAL_PORT (see global.h) to indicate
    // that the packet is generated locally and not received from 
    // a neighbor router.




private:
    Node *sys; // To store Node object; used to access GSR9999 interfaces

    AlarmHandler * alarmHandler;

    unsigned short num_ports;
    unsigned short router_id;
    eProtocolType packet_type;
    void * EMPTY_PACKET;    // Used for flooding

    vector<PortEntry> port_graph;
    unordered_map<uint16_t, DirectNeighborEntry> direct_neighbor_map;   // other router id --- DirectNeighbor   PHYSICAL
    unordered_map<uint16_t, ForwardTableEntry> forward_table;   // other router id --- the next router a packet need to be sent out when receiving it
    unordered_map<uint16_t, DVEntry> DV_table;  // other router id --- cost from this router to OTHER routers

    // LS Part
    uint32_t seq_num;
    unordered_map<uint16_t, unordered_map<uint16_t, LSEntry>> LS_table;
    set<pair<uint16_t, uint32_t>> haveSeenSet;

private:
    // Additional Helper Functions Implemented by Our team
    void init_pingpong();

    void recv_ping_packet(unsigned short port, void *packet, unsigned short size);

    void update_DV(int16_t dest_id,  unsigned int cost, uint16_t next_hop);
    void update_forward(uint16_t dest_id,uint16_t next_hop);
    void update_neighbor(uint16_t neighbor_id, unsigned int cost, uint16_t port_num);

    void recv_data(unsigned short port, void *packet, unsigned short size);

    void recv_dv_packet(unsigned short port, void *packet, unsigned short size);

    void recv_ls_packet(unsigned short port, void *packet, unsigned short size);

    void send_dv_packet();

    void handle_port_expire();

    void handle_dv_expire();

    void printDVTable();

    void printNeighborTable();

    void recv_pong_packet(unsigned short port, void *packet, unsigned short size);

    void insert_neighbor(uint16_t neighbor_id, unsigned int cost, uint16_t port_num);

    void insert_DV(int16_t dest_id, unsigned int cost, uint16_t next_hop);

    void insert_forward(uint16_t dest_id, uint16_t next_hop);

    // LS part:
    void flood_ls_packet(bool isSendMyLSP, uint16_t in_port_num, void * input_packet, int in_packet_size);

    void Dijkstra_update();

    void handle_ls_expire();

    void remove_LS(uint16_t node1_id, uint16_t node2_id);

    bool check_link_in_LSTable(uint16_t node1_id, uint16_t node2_id);

    void insert_LS(uint16_t source_id, uint16_t dest_id, unsigned int cost);

    void update_LS(uint16_t source_id, uint16_t dest_id, unsigned int cost);

    void update_seq_num();

    void printLSTable();


};

#endif

