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
 *         Hybrid RPL (HRPL) extension.
 *
 * HRPL: A Hybrid  IPv6 Routing Protocol for Low-power and Lossy Networks in IoT
 *
 * \author Mohammed Mahyoub <g201405280@kfupm.edu.sa><malmeraby@gmail.com>
 */

#include "hrpl.h"
#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"


#if WITH_HRPL

static int hrpl_num_src_route_entries;
LIST(hrpl_routelist);
MEMB(hrpl_routsmemb, hrpl_src_route_t, HRPL_MAX_SRC_ROUTE_ENTRIES);
static struct ctimer periodic_timer;

static uint16_t rreq_seqno = 0;
//static uint16_t rrep_seqno = 0;
int hrpl_hrrep_event;
/*-------------------------------------------------------------------------*/
/*TODO passes the "ip-address" address instead of the "id" */
static void
hrpl_send_hrreq_msg(uint8_t target_id){
	hrreq_msg_t new_msg;
	new_msg.type = HRREQ_TYPE;
	new_msg.seqno = rreq_seqno;
	new_msg.destination = target_id;
	HRPL_LOG("hrreq_send: seq %u  asking for %u \n", new_msg.seqno, target_id);
	simple_udp_sendto(&hrpl_discovery_connection, &new_msg, sizeof(hrreq_msg_t),
			&rpl_get_any_dag()->dag_id);
	rreq_seqno ++;
}
/*--------------------------------------------------------------------------*/
hrpl_src_route_t *
hrpl_has_route_to(const uint8_t dest){
	hrpl_src_route_t * route;
	//int i =0;
	for(route = list_head(hrpl_routelist); route != NULL; route = list_item_next(route)) {
		if(route->dest == dest){
			return route;
		}
	}
	return NULL;
}
/*--------------------------------------------------------------------------*/
void
hrpl_remove_src_route_entry(hrpl_src_route_t *route){
	  list_remove(hrpl_routelist, route);
	  memb_free(&hrpl_routsmemb, route);
	  hrpl_num_src_route_entries--;
}
/*---------------------------------------------------------------------------*/
uint8_t
hrpl_find_src_route_to_remove(void){
	clock_time_t clock_now = clock_time();
	hrpl_src_route_t *route = list_head(hrpl_routelist);
	hrpl_src_route_t *route_temp = NULL;
	int replacement_strategy = HRPL_REPLACEMENT_STRATEGY;
	switch(replacement_strategy){
	case FIFO_REPLACEMENT_STRATEGY:
		HRPL_LOG("HRPL: the used replacement strategy is FIFO \n");
		for(route_temp = list_head(hrpl_routelist); route_temp != NULL;
				route_temp = list_item_next(route_temp)) {
			if (route_temp->lifetime < route->lifetime){
				route = route_temp;
			}
		}
		break;
	case LRU_REPLACEMENT_STRATEGY:
		HRPL_LOG("HRPL: the used replacement strategy is LRU \n");
		for(route_temp = list_head(hrpl_routelist); route_temp != NULL;
				route_temp = list_item_next(route_temp)) {
			if (clock_now - route_temp->last_time_use > clock_now - route->last_time_use){
				route = route_temp;
			}
		}
		break;
	case LFU_REPLACEMENT_STRATEGY:
		HRPL_LOG("HRPL: the used replacement strategy is LFU \n");
		for(route_temp = list_head(hrpl_routelist); route_temp != NULL;
				route_temp = list_item_next(route_temp)) {
			if (route_temp->num_hits < route->num_hits){
				route = route_temp;
			}
		}
		break;
	case NULL_REPLACEMENT_STRATEGY:
    default:
    	HRPL_LOG("HRPL: the used replacement strategy is NULL \n");
    	route = NULL;
    	break;
	}
	if(route == NULL){
		return 0;
	}else{
	  hrpl_remove_src_route_entry(route);
	  HRPL_LOG("HRPL: remove the src_entry of the destination %u\n", route->dest);
  	  return 1;
	}
}
/*---------------------------------------------------------------------------*/
void
hrpl_proccessng_received_hrrep_msg(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,
        uint16_t sender_port,
        const uip_ipaddr_t *receiver_addr,
        uint16_t receiver_port,
        const uint8_t *dataptr,
        uint16_t datalen){

	hrrep_msg_t *msg = (hrrep_msg_t *)dataptr;
	hrpl_src_route_t *route = NULL;
	route= hrpl_has_route_to(msg->destination);
	if(route == NULL){
		if (hrpl_num_src_route_entries > HRPL_MAX_SRC_ROUTE_ENTRIES){
			HRPL_LOG("HRPL: no space for route, the replacement algorithm is called\n");
			if(!hrpl_find_src_route_to_remove()){
				HRPL_LOG("src_route_dropped: replacement strategy fails to remove a src_entry\n");
				return;
			}
		}
		route = memb_alloc(&hrpl_routsmemb);
		if(route==NULL){
			return ;
		}
		list_add(hrpl_routelist, route);
		route->num_hits = 1;
		route->last_time_use = clock_time();
		hrpl_num_src_route_entries++;
	}
	route->dest = msg->destination;
	route->len = msg->path_len;
	route->etx = msg->path_etx;
	route->lifetime = HRPL_MAX_LIFETIME;
	memcpy(route->path, msg->path, HRPL_MAX_SRC_ROUTE_LENGTH);
	HRPL_LOG("hrrep_recv:  seq: %u about: %u \n",  msg->seqno, msg->destination);

	uint8_t i;
	HRPL_LOG("HRPL: route added/updated, dest:%u, len:%u, etx:%u, path: [%u <-",
			route->dest, route->len, route->etx, route->dest);
	for(i=0; i< route->len-1; i++){
				HRPL_LOG("%u <-",msg->path[i]);
	}
	HRPL_LOG(" %u], lifetime:%lu sec\n",node_id, route->lifetime);
	process_post_synch(&udp_hrpl_process, hrpl_hrrep_event, NULL);
}
/*----------------------------------------------------------------------------*/
/*TODO hrpl route reply error */
/*static void
hrrer_processing(uint16_t seqno, uint16_t originator, uint16_t destination){

	PRINTF("HRPL: rt-discovery hrrer received\n");
}*/
/*---------------------------------------------------------------------------*/
void
hrpl_print_route_list()
{
	hrpl_src_route_t *route;
	uint8_t i=0;
	HRPL_LOG("HRPL: route_list beginning\n");
	HRPL_LOG("dest  len   etx   num_hits        path(reversed)    lifetime \n");
	for(route = list_head(hrpl_routelist); route != NULL; route = list_item_next(route)) {
		HRPL_LOG("%2u %5u %5u   %5u       [%u",
				route->dest, route->len, route->etx, route->num_hits, route->dest);
		for(i=0; i< route->len-1; i++){
			HRPL_LOG("<- %u",route->path[i]);
		}
		HRPL_LOG("<- %u] %7lu \n",node_id, route->lifetime);
	}
	HRPL_LOG("HRPL: route_list end\n");
}
/*---------------------------------------------------------------------------*/
void
hrpl_handle_routes_table_periodic_timer(void *ptr){
	hrpl_src_route_t *l;
	//pass and decrement lifetime for all nodes with non-infinite lifetime
	for(l = list_head(hrpl_routelist); l != NULL; l = list_item_next(l)) {
		if(l->lifetime > 0) {
		  l->lifetime=l->lifetime-60;
		  PRINTF("HRPL: decrement src_entry lifetime  of the destination %u \n", l->dest);
		  // Deallocate the route with lifetime zero
		  if(l->lifetime < 1) {
			  PRINTF("HRPL: remove the expired src_entry of the destination %u \n", l->dest);
			  hrpl_remove_src_route_entry(l);
		  }
		}
	}
	ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
hrpl_routes_table_periodic(void){
	  ctimer_set(&periodic_timer, 60 * (clock_time_t) CLOCK_SECOND,
			  hrpl_handle_routes_table_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
void hrpl_discover_route_to(const uint8_t target_id)
{
	hrpl_send_hrreq_msg(target_id);
}
/*----------------------------------------------------------------------------*/
void
hrpl_discovery_manager_init(void)
{
	  memb_init(&hrpl_routsmemb);
	  list_init(hrpl_routelist);
	  hrpl_num_src_route_entries =0;
	  hrpl_routes_table_periodic();
}
/*---------------------------------------------------------------------------*/

#endif /* WITH_HRPL*/
