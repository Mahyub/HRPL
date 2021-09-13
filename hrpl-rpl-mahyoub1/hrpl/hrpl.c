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
uint8_t suggested_etx;
/*---------------------------------------------------------------------------*/
static void
hrpl_set16(uint8_t *buffer, int pos, uint16_t value)
{
  buffer[pos++] = value >> 8;
  buffer[pos++] = value & 0xff;
}
/*---------------------------------------------------------------------------*/
int
hrpl_lookup(uint8_t target){
	hrpl_src_route_t * route = NULL;
	route = hrpl_has_route_to(target);
	if(route != NULL){
		PRINTF("HRPL: there is route to %u\n",target);
		route->last_time_use = clock_time();
		route->num_hits++;
		suggested_etx = route->etx;
		return 1;
	}else{
		hrpl_discover_route_to(target);
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
int
hrpl_insert_neighbors_metric(unsigned char *buffer, int pos){
	int curr_pos = pos;
	int counter=0;
	uint16_t etx_diff;
	struct link_stats * nbr_stats = NULL;
	clock_time_t clock_now = clock_time();
	uip_ds6_nbr_t *nbr = nbr_table_head(ds6_neighbors);
	while(nbr != NULL) {
		const linkaddr_t *nbr_lladdr;
		nbr_lladdr = nbr_table_get_lladdr(ds6_neighbors, nbr);
		nbr_stats = link_stats_from_lladdr(nbr_lladdr);
		if(nbr_stats != NULL){
			etx_diff = (nbr_stats->etx > nbr_stats->sent_etx)? (nbr_stats->etx - nbr_stats->sent_etx):
					(nbr_stats->sent_etx - nbr_stats->etx);
			if((etx_diff > (HRPL_UPDATE_SEND_THRESHOLD * 128)) ||
					(clock_now - nbr_stats->last_time_etx_sent > HRPL_MIN_UPDATE_INTERVAL ||
							nbr_stats->sent_flag==0)){
				buffer[curr_pos++] = HRPL_OPTION_NEIGHBOUR_INFO;
				buffer[curr_pos++] = 4;  //the length of the NEIGHBOUR_INFO option is 4 bytes
				hrpl_set16(buffer, curr_pos, (uint16_t)nbr_lladdr->u8[LINKADDR_SIZE - 1]);
				curr_pos += 2;
				hrpl_set16(buffer, curr_pos, nbr_stats->etx);
				curr_pos += 2;
				PRINTF("HRPL: send metric info. for neighbor %u, curr_etx: %u, sent_etx: %u, etx_diff: %u\n",
						nbr_lladdr->u8[LINKADDR_SIZE - 1],nbr_stats->etx, nbr_stats->sent_etx, etx_diff);
				nbr_stats->sent_etx =  nbr_stats->etx;
				nbr_stats->last_time_etx_sent = clock_now;
				nbr_stats->sent_flag=1;
				counter++;
			}else{
				PRINTF("HRPL: suppress metric info. for neighbor %u, curr_etx: %u, sent_etx: %u, etx_diff: %u\n",
						nbr_lladdr->u8[LINKADDR_SIZE - 1],nbr_stats->etx, nbr_stats->sent_etx, etx_diff);
			}
		}
		nbr = nbr_table_next(ds6_neighbors, nbr);
	 }
//	printf("pos number of neibors agregated to dao = %d\n",counter);
	return curr_pos;
}
/*-------------------------------------------------*/
void
hrpl_open_discovery_connection(int is_root)
{
	int discovery_conn=0;
	if(is_root){
	discovery_conn= simple_udp_register(&hrpl_discovery_connection, HRREP_PORT,
						NULL, HRREQ_PORT,	hrpl_proccessng_received_hrreq_msg);
	}else{
		discovery_conn= simple_udp_register(&hrpl_discovery_connection, HRREQ_PORT,
							NULL, HRREP_PORT,	hrpl_proccessng_received_hrrep_msg);
	}
	if(discovery_conn){
		PRINTF("HRPL: discovery connection is created\n");
	}else{
		PRINTF("HRPL: discovery connection isn't be created\n");
	}
}
/*-------------------------------------------------*/
void
hrpl_init(is_root)
{
	if(is_root){
		hrpl_link_manager_init();
		hrpl_route_manager_init();
	}else{
		hrpl_discovery_manager_init();
		hrpl_hrrep_event = process_alloc_event();
	}
	hrpl_open_discovery_connection(is_root);
}
#endif /* WITH_HRPL */
