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
 *         Example how to use the HRPL extension.
 *
 * This program has been written for Contiki v3.0, Cooja and wismote motes
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 *
 */
#include "contiki.h"
#include "lib/random.h"
#include "uip-ds6.h"
#include "simple-udp.h"
#include "simple-energest.h"
#include <stdio.h>
#include <string.h>
#include "sys/etimer.h"
#include "sys/node-id.h"
#include "hrpl-tools.h"
#if WITH_HRPL
#include "hrpl.h"
#endif /* WITH_HRPL */
#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UDP_PORT 8765

#ifndef PERIOD
#define PERIOD 2
#endif /* PERIOD */

#define TIME_BEFORE_APP		(2 * 60 * CLOCK_SECOND)
#define SEND_INTERVAL		(60 * CLOCK_SECOND /PERIOD)
#define TIMEOUT 10
static struct simple_udp_connection conn;
static uip_ipaddr_t target;
static uint16_t id;
uip_ipaddr_t my_ipaddr;
static uint16_t seqno = 0;
#if WITH_HRPL
int use_hrpl_route;
#endif /* WITH_HRPL */
uint8_t suggested_etx;
/*---------------------------------------------------------------------------*/
PROCESS(udp_hrpl_process, "app-p2p-node");
AUTOSTART_PROCESSES(&udp_hrpl_process);
/*---------------------------------------------------------------------------*/
static void
receiver(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,
        uint16_t sender_port,
        const uip_ipaddr_t *receiver_addr,
        uint16_t receiver_port,
        const uint8_t *dataptr,
        uint16_t datalen)
{
	  struct app_data data;
	  app_copy_data(&data, (struct app_data*)dataptr);
	  HRPL_LOG("app_recv: seq: %lu hops: %u sugg_etx: %u actual_etx: %u src: %u dest: %u\n",
			  data.seqno, data.hop, data.sugg_etx, data.actual_etx, data.src, data.dest);
}
/*---------------------------------------------------------------*/
static void
get_target_address(){
	static uint16_t index;
	index = random_rand();
	do {
	  id = 1 + (index++ % N_NODES) ;
	} while (!is_id_in_receiving_list(id));
	hrpl_get_global_addr(&target, id);
}
/*---------------------------------------------------------------*/
uint16_t
get_sending_time(){
	uint16_t sending_time ;
	do {
		sending_time = random_rand() % (SEND_INTERVAL);
	} while (sending_time > (SEND_INTERVAL - TIMEOUT * CLOCK_SECOND));
	return sending_time;
}
/*----------------------------------------------------------------*/
static void
send_packet(void)
{
	  struct app_data data;
	  data.magic = HRPL_LOG_MAGIC;
	  data.seqno = seqno;
	  data.src = node_id;
	  data.hop = 0;
	  data.sugg_etx = 0;
	  data.dest = target.u8[sizeof(target.u8) - 1];
#if WITH_HRPL
	  if(use_hrpl_route)
	  {
		  data.sugg_etx = suggested_etx;
		  HRPL_LOG("HRPL: ++++++++++++ (HRPL ROUTING) ++++++++++\n");
	  }
	  else
#endif /* WITH_HRPL */
		  HRPL_LOG("HRPL: ============ (RPL ROUTING) ===========\n");
	  HRPL_LOG("app_send: seq: %u to: %u \n",seqno, (uint16_t)data.dest);
	  simple_udp_sendto(&conn, &data, sizeof(data), &target);
	  seqno++;
#if WITH_HRPL
	  use_hrpl_route = 0;
#endif /* WITH_HRPL */
}
/*----------------------------------------------------------------*/

PROCESS_THREAD(udp_hrpl_process, ev, data)
{
  static struct etimer before_app_timer;
  static struct etimer periodic_timer;
  static struct etimer send_timer;
  uint8_t timeout=5;
  PROCESS_BEGIN();
  if(node_id == 0) {
    NETSTACK_RDC.off(0);
    PROCESS_EXIT();
  }
  simple_energest_start();
  hrpl_get_global_addr(&my_ipaddr, node_id);
  uip_ds6_addr_add(&my_ipaddr, 0, ADDR_AUTOCONF);
  print_local_addresses();
  /* new connection with remote host */
  if(simple_udp_register(&conn, UDP_PORT, NULL, UDP_PORT, receiver)){
	  HRPL_LOG("new udp socket is registered\n");
  }
#if WITH_HRPL
  static struct etimer timeout_timer;
  use_hrpl_route = 0;
  hrpl_init(0); //hrpl_init(is_root)

#endif /* WITH_HRPL */
  if(is_id_in_receiving_list(node_id)){
	  HRPL_LOG("I am in the receiving list\n");
  }
  if(is_id_in_sending_list(node_id)){
		HRPL_LOG("I am node %u in the sending list\n",node_id);
		etimer_set(&before_app_timer, TIME_BEFORE_APP);
	    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&before_app_timer));
		etimer_set(&periodic_timer, SEND_INTERVAL);
		while(1) {
		    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
		    etimer_reset(&periodic_timer);
			get_target_address();
		    //To insure that we will send new packet after the previous one was sent
		    etimer_set(&send_timer, get_sending_time() );
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&send_timer));
#if WITH_HRPL
			if(hrpl_lookup(target.u8[sizeof(target.u8) - 1])){
//				hrpl_print_route_list();
				use_hrpl_route =1;
				send_packet();
			}else{
				etimer_set(&timeout_timer, CLOCK_SECOND * TIMEOUT);
				PROCESS_WAIT_EVENT();
				if(ev == hrpl_hrrep_event){
					if(hrpl_lookup(target.u8[sizeof(target.u8) - 1])){
						use_hrpl_route = 1;
					}
					etimer_stop(&timeout_timer);
//					hrpl_print_route_list();
					send_packet();
				}else if(ev == PROCESS_EVENT_TIMER){
					HRPL_LOG("timeout_timer:  hrreq timer about %u expired, use RPL\n",
							target.u8[sizeof(target.u8) - 1]);
					send_packet();
				}
			}
#else /* WITH_HRPL */
			send_packet();
#endif /* WITH_HRPL */
		}
	}
  PROCESS_END();
}
/*-----------------------------------------------------------------*/
