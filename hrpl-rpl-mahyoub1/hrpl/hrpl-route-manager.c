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

typedef struct dijkstra_array{
	uint16_t array [N_NODES+1];
}dijkstra_array_t;

MEMB(hrpl_dijkstra_arrays_memb, dijkstra_array_t , 3);

/*---------------------------------------------------------------------------*/
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
uint8_t minDistance(uint16_t *dist, uint16_t *sptSet)
{
    // Initialize min value
	uint16_t min = INT_MAX;
	uint8_t min_index = 0;
	uint8_t v;
    for (v = 0; v < N_NODES+1; v++){
        if (sptSet[v] == 0 && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}
/*---------------------------------------------------------------------------*/
uint8_t
hrpl_dijkstra(uint8_t src, uint8_t target, path_info_t * path_info){

	uint8_t route_is_found=0;
    //hrpl_node_t* node = NULL;

	/*The output array.  distance[i] will hold the shortest distance from src to i*/
	dijkstra_array_t *distance = NULL; //pointer to integer
	dijkstra_array_t *parent = NULL; //pointer to integer used later to print the path
	dijkstra_array_t *sptSet = NULL; //pointer to integer used later to print the path

	distance = memb_alloc(&hrpl_dijkstra_arrays_memb);
	parent   = memb_alloc(&hrpl_dijkstra_arrays_memb);
	sptSet   = memb_alloc(&hrpl_dijkstra_arrays_memb);

    /*Initialize all distances as INFINITE and stpSet[] as false*/
    uint8_t i;
    for (i = 0; i < N_NODES+1; i++){
    	distance->array[i] = INT_MAX;
        sptSet->array[i] = 0;
        parent->array[i] = -1;
    }
//    hrpl_print_all_node_list();
    /*Distance of source vertex from itself is always 0*/
    distance->array[src] = 0;
	/*Find shortest path for all vertices*/
    uint8_t count;

    for (count = 0; count < N_NODES+1; count++) {
    	/*Pick the minimum distance vertex from the set of vertices not
        yet processed. u is always equal to src in the first iteration.*/
    	uint8_t u = minDistance(distance->array, sptSet->array);
        /*Mark the picked vertex as processed*/
        sptSet->array[u] = 1;
        if(u==target){
			route_is_found =1;
				break;
		}

        /*Update dist value of the adjacent vertices of the picked vertex.*/
        hrpl_parent_node_t* myParent = list_head(hrpl_get_node_by_id(u)->parent_list);
        while (myParent != NULL)
        {
			int v = myParent->id;

			/* If shortest distance to v is not finalized yet, and distance to v
			* through u is less than its previously calculated distance */
			if (!sptSet->array[v] && distance->array[u] != INT_MAX &&
					myParent->link_metric + distance->array[u] < distance->array[v])
			{
				distance->array[v] = distance->array[u] + myParent->link_metric;
				parent->array[v] = u;
			}
			myParent = list_item_next(myParent);
		}
    }
    /*Extract the shortest path to the shortest_path array*/
	if(route_is_found && distance->array[target] != INT_MAX){
		HRPL_LOG("HRPL: path found, ");
		uint8_t  path_array [HRPL_MAX_SRC_ROUTE_LENGTH];
		int start = 0;
		path_info->etx= distance->array[target]/LINK_STATS_ETX_DIVISOR;
		HRPL_LOG(" etx:%u, path: [",path_info->etx);
		HRPL_LOG("%d",target);
		for (start = target; start != src; ){
			HRPL_LOG(" <-");
			HRPL_LOG("%d",parent->array[start]);
			start = parent->array[start];
			/*path array includes the destination as the path_array[0]*/
			path_array[(int) path_info->len] = start;
			path_info->len++;
		}
		HRPL_LOG("]\n");
		/*we mean by path_len, the number of hops to the destination*/
		if((int)path_info->len == 1){
			goto clean_and_return;
		}

		/*the destination is excluded from copying so the allocated path has path_len -1 */
		int count =0;
		for(count=0;  count < ((int) path_info->len)-1 ; count++){
			path_info->path[count] = path_array[count];
		}
		goto clean_and_return;
	}else{
		HRPL_LOG("HRPL:  no path found for: %d --> %d\n", src, target);
		route_is_found =0;
		goto clean_and_return;
	}

clean_and_return:
    /* Now free all the allocated memory*/
	memb_free(&hrpl_dijkstra_arrays_memb,distance);
	memb_free(&hrpl_dijkstra_arrays_memb,parent);
	memb_free(&hrpl_dijkstra_arrays_memb,sptSet);
	return route_is_found;
}

/*---------------------------------------------------------------------------*/
/*TODO sending hrpl route reply error */
static void
hrpl_send_hrrer_msg(uint16_t seqno, uint8_t originator, uint8_t destination){
	HRPL_LOG("hrrer_send: no route from %u to %u \n",originator, destination);
}
/*---------------------------------------------------------------------------*/
void
hrpl_send_hrrep_msg(uint16_t seqno, uint8_t originator,
		uint8_t destination, path_info_t * path_info){
	uip_ipaddr_t requester_addr;
	hrrep_msg_t new_msg;
	new_msg.type = HRREP_TYPE;
	new_msg.seqno = seqno;
	new_msg.destination = destination;
	new_msg.path_len = path_info->len;
	new_msg.path_etx =  path_info->etx;
	memcpy(new_msg.path, path_info->path, HRPL_MAX_SRC_ROUTE_LENGTH);

	hrpl_get_global_addr(&requester_addr, originator);
	HRPL_LOG("hrrep_send:  seq %u path from: %u to: %u \n",
			new_msg.seqno, originator, new_msg.destination);
	simple_udp_sendto(&hrpl_discovery_connection, &new_msg,
			sizeof(hrrep_msg_t), &requester_addr);
}
/*---------------------------------------------------------------------------------*/
void
hrpl_proccessng_received_hrreq_msg(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,
        uint16_t sender_port,
        const uip_ipaddr_t *receiver_addr,
        uint16_t receiver_port,
        const uint8_t *dataptr,
        uint16_t datalen){

	hrreq_msg_t *msg = (hrreq_msg_t *)dataptr;
	hrreq_msg_t new_msg;
	new_msg.type = msg->seqno;
	new_msg.seqno = msg->seqno;
	new_msg.destination=msg->destination;
	uint8_t requester = sender_addr->u8[15];
	HRPL_LOG("hrreq_recv:  seq %u looking for: %u to %u\n",
			new_msg.seqno, requester, new_msg.destination);
	if(new_msg.destination == requester){
		PRINTF("HRPL: hrreq_recv where the requester is the destination, return\n ")
		return;
	}
	path_info_t  path_info;
	uint8_t i;
	for(i=0; i<HRPL_MAX_SRC_ROUTE_LENGTH; i++){
		path_info.path[i]=0;
	}
	path_info.len = 0;
	path_info.etx =  0;

	if (hrpl_dijkstra(requester,new_msg.destination, &path_info))
		hrpl_send_hrrep_msg(new_msg.seqno, requester, new_msg.destination, &path_info);
	else
		hrpl_send_hrrer_msg(new_msg.seqno, requester, new_msg.destination);
}
/*---------------------------------------------------------------------------*/
void
hrpl_route_manager_init(void)
{
	memb_init(&hrpl_dijkstra_arrays_memb);
}
/*---------------------------------------------------------------------------*/

#endif /* WITH_HRPL*/
