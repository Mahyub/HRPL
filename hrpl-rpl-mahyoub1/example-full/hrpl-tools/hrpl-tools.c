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
 *
 *
 */
/**
 * \file
 *         Tools for logging HRPL state and tracing data packets
 *
 * \author Simon Duquennoy <simonduq@sics.se>
 * modified by Mohammed Mahyoub <malmeraby@gmail.com>
 */

#include "contiki.h"

#include "net/packetbuf.h"
#include <stdio.h>
#include <string.h>
#include "net/ipv6/uip-ds6.h"
#include "hrpl-tools.h"
#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"
#include "net/rpl/rpl-private.h"
#if WITH_HRPL
#include "hrpl.h"
#endif /* WITH_HRPL */

uip_ipaddr_t prefix;

static  uint16_t sending_list[]= {

#if N_FLOWS == 8
	11,16,21,26,31,36,41,46,

#elif N_FLOWS == 16
	11,12,16,17,21,22,26,27,31,32,36,37,41,42,46,47,

#elif N_FLOWS == 24
	11,12,13,16,17,18,21,22,23,26,27,28,31,32,33,36,37,38,41,42,43,46,47,48,

#endif
	0
};

/*---------------------------------------------------------------------------------------*/
static  uint16_t receiving_list[]= {

#if N_NODES == 20
	3,4,7,8,11,12,15,16,19,20,

#elif N_NODES == 40
	3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39,40,

#elif N_NODES == 50
	4,5,9,10,14,15,19,20,24,25,29,30,34,35,39,40,44,45,49,50,
#endif
	0
};

/*-----------------------------------------------------*/
int is_id_in_sending_list(uint16_t id) {
  uint16_t *curr = sending_list;
  while(*curr != 0) {
    if(*curr == id) {
      return 1;
    }
    curr++;
  }
  return 0;
}
/*---------------------------------------------------------------------------------------*/

int is_id_in_receiving_list(uint16_t id){
	uint16_t *curr1 = receiving_list;
	while(*curr1 != 0) {
	  if(*curr1 == id) {
		return 1;
	  }
	  curr1++;
	}
	return 0;
}

/*---------------------------------------------------------------------------------------*/
void hrpl_get_global_addr(uip_ipaddr_t *addr,uint16_t id) {
	uip_ip6addr(&prefix, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
	memcpy(addr, &prefix,16);
	addr->u8[8] = 2;
	addr->u8[15] = id;
}
/*---------------------------------------------------------------------------*/
void
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
/*---------------------------------------------------------------------------------------*/
/* Copy an appdata to another with no assumption that the addresses are aligned */
void
app_copy_data(struct app_data *dst, struct app_data *src)
{
  int i;
  for(i=0; i<sizeof(struct app_data); i++) {
    ((char*)dst)[i] = (((char*)src)[i]);
  }
}
/*---------------------------------------------------------------------------------------*/
/* Get dataptr from the packet currently in uIP buffer */
struct app_data *
appdataptr_from_uip()
{
  return (struct app_data *)((char*)uip_buf + ((uip_len - sizeof(struct app_data))));
}
/*---------------------------------------------------------------------------------------*/
/* Get dataptr from the current packetbuf */
struct app_data *
appdataptr_from_packetbuf()
{
  struct app_data *ptr;
  struct app_data data;
  if(packetbuf_datalen() < sizeof(struct app_data)) return NULL;
  ptr = (struct app_data *)((char*)packetbuf_dataptr() + ((packetbuf_datalen() - sizeof(struct app_data))));
  app_copy_data(&data, ptr);
  if(data.magic == HRPL_LOG_MAGIC) {
    return ptr;
  } else {
    return NULL;
  }
}
/*---------------------------------------------------------------------------------------*/
/* Log information about a data packet along with HRPL routing information */
void
log_appdataptr(struct app_data *dataptr)
{
  struct app_data data;
  if(dataptr) {
	  app_copy_data(&data, dataptr);

	  HRPL_LOG("seq: %lu src: %u dest: %u\n",
        data.seqno,
        data.src,
        data.dest
        );
  }

}
/*---------------------------------------------------------------------------------------*/
void uip_statistics_print() {
	  HRPL_LOG("stack_stats:  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u\n",
			  uip_stat.ip.sent, uip_stat.ip.recv, uip_stat.ip.forwarded, uip_stat.ip.drop,
			  uip_stat.udp.sent, uip_stat.udp.recv, uip_stat.udp.drop,
			  uip_stat.icmp.sent, uip_stat.icmp.recv, uip_stat.icmp.drop,
			  uip_stat.nd6.sent, uip_stat.nd6.recv, uip_stat.nd6.drop);
}
/*-----------------------------------------------------------------------------------------*/
void rpl_stats_print() {
	  HRPL_LOG("rpl_stats:  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  \n",
			  rpl_stats.mem_overflows, rpl_stats.local_repairs, rpl_stats.global_repairs,
			  rpl_stats.malformed_msgs, rpl_stats.resets, rpl_stats.parent_switch,
			  rpl_stats.forward_errors, rpl_stats.loop_errors, rpl_stats.loop_warnings,
			  rpl_stats.root_repairs);
}
/*-----------------------------------------------------------------------------------------*/
