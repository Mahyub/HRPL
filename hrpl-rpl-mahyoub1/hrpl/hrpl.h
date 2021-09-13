/*
 * Copyright (c) 2019, Mohammed Mahyoub
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/**
 * \file
 *         Hybrid RPL  (HRPL) extension.
 *
 * H-RPL: A Hybrid  IPv6 Routing Protocol for Low-power and Lossy Networks in IoT
 *
 * \author Mohammed Mahyoub <g201405280@kfupm.edu.sa>,<malmeraby@gmail.com>
 * Contributor:
 */

#ifndef HRPL_H
#define HRPL_H

#include "net/rpl/rpl.h"
#include "simple-udp.h"
#include "net/rpl/rpl-ns.h"
#include "net/nbr-table.h"
#include "net/rpl/rpl-private.h"
#include "lib/list.h"
#include "lib/memb.h"
#include "sys/ctimer.h"
#include "lib/random.h"
#include <limits.h>
#include <string.h>
#include "sys/etimer.h"
#include "sys/node-id.h"
#include "sys/ctimer.h"
#include "lib/random.h"
#include <stdio.h>
#include "link-stats.h"
#include "net/ipv6/uip-ds6-nbr.h"

#include "hrpl-tools.h"

#define HRREQ_PORT 6665
#define HRREP_PORT 6666
struct simple_udp_connection hrpl_discovery_connection;
#define HRREQ_TYPE 0X0
#define HRREP_TYPE 0X1
#define HRREP_ACK_TYPE 0X2
#define HRERR_TYPE 0X3

#define NULL_REPLACEMENT_STRATEGY 0
#define FIFO_REPLACEMENT_STRATEGY 1
#define LRU_REPLACEMENT_STRATEGY 2
#define LFU_REPLACEMENT_STRATEGY 3

/* Hysteresis of UMHUF: the metric must differ more than HRPL_UPDATE_SEND_THRESHOLD
 * in order to send the new update about the metric value of a neighbor .
 * As we use the same concept in Hysteresis of MRHOF:
 * Default in RFC6719 for (PARENT_SWITCH_THRESHOLD) is 192, eq ETX of 1.5 .
 * Contiki uses a more aggressive setting: 96, eq ETX of 0.75
 * In HRPL we use the same value as in RFC6719: ETX of 192, eq ETX
 */
#ifdef HRPL_CONF_UPDATE_SEND_THRESHOLD
#define HRPL_UPDATE_SEND_THRESHOLD HRPL_CONF_UPDATE_SEND_THRESHOLD
#else  /* HRPL_CONF_UPDATE_SEND_THRESHOLD */
#define HRPL_UPDATE_SEND_THRESHOLD 1.5 /* Eq ETX of 1.5 */
#endif  /* HRPL_CONF_UPDATE_SEND_THRESHOLD */

#ifdef HRPL_CONF_MAX_LINK_METRIC
#define HRPL_MAX_LINK_METRIC HRPL_CONF_MAX_LINK_METRIC
#else  /* HRPL_CONF_MAX_LINK_METRIC */
#define HRPL_MAX_LINK_METRIC 1024 /* Eq ETX of 8 */
#endif  /* HRPL_CONF_MAX_LINK_METRIC */

#ifdef HRPL_CONF_MAX_LINK_NUM
#define HRPL_MAX_LINK_NUM HRPL_NS_CONF_LINK_NUM
#else  /* HRPL_CONF_MA_LINK_NUM */
#define HRPL_MAX_LINK_NUM (RPL_NS_LINK_NUM * 4)
#endif  /* HRPL_CONF_MAX_LINK_NUM */

#ifdef HRPL_CONF_MAX_SRC_ROUTE_ENTRIES  //number of cached hrpl_route entries
#define HRPL_MAX_SRC_ROUTE_ENTRIES HRPL_CONF_MAX_SRC_ROUTE_ENTRIES
#else  /* HRPL_CONF_MAX_SRC_ROUTE_ENTRIES */
#define HRPL_MAX_SRC_ROUTE_ENTRIES 8
#endif  /* HRPL_CONF_MAX_SRC_ROUTE_ENTRIES */

#ifdef HRPL_CONF_MAX_LIFETIME  //route lifetime in the cache
#define HRPL_MAX_LIFETIME HRPL_CONF_MAX_LIFETIME
#else  /* HRPL_CONF_MAX_LIFETIME */
#define HRPL_MAX_LIFETIME RPL_DEFAULT_LIFETIME * RPL_DEFAULT_LIFETIME_UNIT
#endif  /* HRPL_CONF_MAX_LIFETIME */

#ifdef HRPL_CONF_MIN_UPDATE_INTERVAL  //route lifetime in the cache
#define HRPL_MIN_UPDATE_INTERVAL HRPL_CONF_MIN_UPDATE_INTERVAL
#else  /* HRPL_CONF_MIN_UPDATE_INTERVAL */
#define HRPL_MIN_UPDATE_INTERVAL ((HRPL_MAX_LIFETIME - 100) * (clock_time_t)CLOCK_SECOND)
#endif  /* HRPL_CONF_MIN_UPDATE_INTERVAL */

#ifdef HRPL_CONF_MAX_SRC_ROUTE_LENGTH  //maximum length of the hrpl_source_route
#define HRPL_MAX_SRC_ROUTE_LENGTH HRPL_CONF_MAX_SRC_ROUTE_LENGTH
#else  /* HRPL_CONF_MAX_SRC_ROUTE_LENGTH */
#define HRPL_MAX_SRC_ROUTE_LENGTH 15
#endif  /* HRPL_CONF_MAX_SRC_ROUTE_LENGTH */

#ifdef HRPL_CONF_REPLACEMENT_STRATEGY  //replacement algorithm
#define HRPL_REPLACEMENT_STRATEGY HRPL_CONF_REPLACEMENT_STRATEGY
#else  /* HRPL_CONF_REPLACEMENT_STRATEGY */
#define HRPL_REPLACEMENT_STRATEGY FIFO_REPLACEMENT_STRATEGY
#endif  /* HRPL_CONF_REPLACEMENT_STRATEGY */

extern uint8_t suggested_etx;
extern int use_hrpl_route;
extern int hrpl_hrrep_event;

uint16_t update_metric_count;    /* Total number of sent updated metric (i.e. etx updates) */

/** brief An entry in the  information table managed by the root */
typedef struct hrpl_node {
	struct hrpl_node *next;
	uint8_t id;
	/* Each information entry belongs to a specific node. That entry
	     holds a list of all its neighborhood information. The parents field
	     point to the hrpl_parent_node that is one parent for the node. */
	//uint8_t num_parents;
	LIST_STRUCT(parent_list);
}hrpl_node_t;

/** \brief A node_parents list entry, used on the
    hrpl_node->node_parents->parent_list list. */
typedef struct hrpl_parent_node {
  struct hrpl_parent_node *next;
  //rpl_dag_t *dag;
  uint32_t lifetime;
  uint16_t link_metric;
  uint8_t id;
} hrpl_parent_node_t;

typedef struct {
	uint8_t path[HRPL_MAX_SRC_ROUTE_LENGTH];
	uint8_t len;
	uint8_t etx;
}path_info_t;

typedef struct hrreq_msg{
	uint8_t type;
	uint16_t seqno;
	uint16_t destination;
}hrreq_msg_t;

typedef struct hrrep_msg{
	uint8_t type;
	uint16_t seqno;
	uint8_t destination;
	uint8_t path_len;
	uint8_t path_etx;
	uint8_t path[HRPL_MAX_SRC_ROUTE_LENGTH];
}hrrep_msg_t;

typedef struct rerr_message_struture {
	uint8_t type;
	uint8_t errorcode;
	uint8_t destination;
}hrerr_message;

typedef struct hrpl_src_route {
	struct hrpl_src_route* next;
	uint8_t dest;
	uint8_t len;
	uint8_t etx;
	uint8_t path[HRPL_MAX_SRC_ROUTE_LENGTH];
	uint32_t lifetime;
	clock_time_t last_time_use;
	uint8_t num_hits;
}hrpl_src_route_t;

void hrpl_init(int is_root);
void hrpl_link_manager_init(void);
void hrpl_route_manager_init(void);
void hrpl_discovery_manager_init(void);

hrpl_node_t * hrpl_get_node_by_id(uint8_t id);
void hrpl_print_route_list(void);

hrpl_src_route_t * hrpl_has_route_to(uint8_t dest);
void hrpl_discover_route_to(uint8_t target_id);
int hrpl_lookup(uint8_t target);

int hrpl_insert_neighbors_metric(unsigned char *buffer, int pos);
hrpl_node_t *hrpl_update_neighbors_metric(rpl_dag_t *dag, const uip_ipaddr_t *child,
		uint8_t neigbour_id,  uint16_t link_metric);

void hrpl_proccessng_received_hrreq_msg(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,  uint16_t sender_port,
		const uip_ipaddr_t *receiver_addr,  uint16_t receiver_port,
        const uint8_t *dataptr,  uint16_t datalen);

void hrpl_proccessng_received_hrrep_msg(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,
        uint16_t sender_port,
        const uip_ipaddr_t *receiver_addr,
        uint16_t receiver_port,
        const uint8_t *dataptr,
        uint16_t datalen);

PROCESS_NAME(udp_hrpl_process);

#endif /* HRPL_H */
