//
// Created by Hanyi Wang on 3/30/20.
//

#ifndef PROJECT3_UTILS_H
#define PROJECT3_UTILS_H

#include "global.h"

#define PINGPONG_PACKET_SIZE 12

struct PortEntry {
    uint16_t to_router_id;
    unsigned int cost;
    unsigned int last_update_time;
//    bool is_connect;
};

struct DirectNeighborEntry {
    uint16_t port_num;
    uint16_t router_id;
    unsigned int cost;
};

struct DVEntry {
    uint16_t next_hop;
    unsigned int cost;
};

struct ForwardTableEntry {
    uint16_t port_id;
};

#endif //PROJECT3_UTILS_H
