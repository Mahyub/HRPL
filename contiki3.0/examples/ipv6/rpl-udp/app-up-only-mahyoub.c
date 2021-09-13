/*
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
 *
 * This file is part of the Contiki operating system.
 *
 */

#include "contiki.h"
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/rtimer.h"
#include "net/ip/uip.h"
#include "net/rpl/rpl.h"
#include "net/ipv6/uip-ds6.h"
#include "simple-udp.h"
#ifdef WITH_COMPOWER
#include "powertrace.h"
#endif
#include <stdio.h>
#include <string.h>
#include "net/ipv6/uip-ds6-route.h"
#include "sys/node-id.h"

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UDP_PORT 8765
#ifndef PERIOD
#define PERIOD 50
#endif
#define SEND_INTERVAL		(PERIOD * CLOCK_SECOND)
#define SEND_TIME		(random_rand() % (SEND_INTERVAL))
#define MAX_PAYLOAD_LEN		32
#define N_NODES 31
#define ROOT_ID 1
static struct simple_udp_connection conn;
static uip_ipaddr_t target;
uip_ipaddr_t my_ipaddr;
uip_ipaddr_t prefix;
rtimer_clock_t start_time;
/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/
static void
receiver(struct simple_udp_connection *c,
        const uip_ipaddr_t *sender_addr,
        uint16_t sender_port,
        const uip_ipaddr_t *receiver_addr,
        uint16_t receiver_port,
        const uint8_t *data,
        uint16_t datalen)
{
	printf("Mahyoub\n");
	  uip_ipaddr_t src ;
	  uip_ipaddr_copy(&src, &UIP_IP_BUF->srcipaddr);
	  PRINTF("DATA recv from %u\n", src.u8[sizeof(src) - 1]);
	  PRINT6ADDR(&src);
	  PRINTF("\n");
}
/*---------------------------------------------------------------------------*/
static void
get_target_address(){
	uint16_t id;
	do {
	  id = 1 ;
	  memcpy(&target, &prefix, 8);
	  target.u8[8] = target.u8[10] = target.u8[12] = target.u8[14] = id >> 8;
	  target.u8[9] = target.u8[11] = target.u8[13] = target.u8[15] = id;
	} while (id==node_id);
	PRINTF("The target address is ");
	PRINT6ADDR(&target);
	printf("\n");
}
/*---------------------------------------------------------------------------*/
static void
send_packet(void)
{
	  uint8_t payload[MAX_PAYLOAD_LEN] = { 0 };
	  get_target_address();
	  printf("DATA send to %d\n",target.u8[sizeof(target.u8) - 1]);
	  simple_udp_sendto(&conn, &payload, 2, &target);
}
/*---------------------------------------------------------------------------*/
static void
print_local_addresses(void)
{
  int i;
  uint8_t state;

  PRINTF("Client IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
      /* hack to make address "final" */
      if (state == ADDR_TENTATIVE) {
	uip_ds6_if.addr_list[i].state = ADDR_PREFERRED;
      }
    }
  }
}
/*---------------------------------------------------------------------------*/
void set_my_global_addr() {
	uip_ip6addr(&prefix, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
	memcpy(&my_ipaddr, &prefix, 8);
	my_ipaddr.u8[8] = my_ipaddr.u8[10] = my_ipaddr.u8[12] = my_ipaddr.u8[14] = node_id >> 8;
	my_ipaddr.u8[9] = my_ipaddr.u8[11] = my_ipaddr.u8[13] = my_ipaddr.u8[15] = node_id;
	uip_ds6_addr_add(&my_ipaddr, 0, ADDR_AUTOCONF);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{

  struct uip_ds6_addr *root_if;
  static struct etimer periodic;
  int connection;
  PROCESS_BEGIN();
  set_my_global_addr();
  PRINTF("UDP client process started nbr:%d routes:%d\n",
         NBR_TABLE_CONF_MAX_NEIGHBORS, UIP_CONF_MAX_ROUTES);
  print_local_addresses();
  /* new connection with remote host */
  connection = simple_udp_register(&conn, UDP_PORT, NULL, UDP_PORT, receiver);
  if (connection){
	printf("New simple_udp_connectio was being created\n");
	} else{
		printf("The simple_udp_connection is rejected\n");
	}

  if(node_id == ROOT_ID) {

	  /* The data sink runs with a 100% duty cycle in order to ensure high
	     packet reception rates. */
	  NETSTACK_MAC.off(1);
	  start_time = RTIMER_NOW();
	  PRINTF("start_time is %\n", (RTIMER_ARCH_SECOND*60));
	  root_if = uip_ds6_addr_lookup(&my_ipaddr);
	  if(root_if != NULL) {
	    rpl_dag_t *dag;
	    rpl_set_root(RPL_DEFAULT_INSTANCE,&my_ipaddr);
	    dag = rpl_get_any_dag();
	    rpl_set_prefix(dag, &prefix, 64);
	    PRINTF("created a new RPL dag\n");
	  }
	  else {
	    PRINTF("failed to create a new RPL DAG\n");
	  }

	  while(1) {
	    PROCESS_WAIT_EVENT();
	  }
  } else {
	  etimer_set(&periodic, SEND_TIME);
	  while(1) {
		  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic));
		  send_packet();
		  etimer_reset(&periodic);
	  	  }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
