/*
 * Copyright (c) 2019, Mohammed Mahyoub.
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
 * This program has been written for Cooja and wismote motes
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 *
 */

#include "contiki.h"
#include "net/rpl/rpl.h"
#include "net/ipv6/uip-ds6.h"
#include "simple-energest.h"
#include <stdio.h>
#include <string.h>
#include "sys/node-id.h"
#include "hrpl-tools.h"

#if WITH_HRPL
#include "hrpl.h"
#endif /* WITH_HRPL */

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UDP_PORT 8765
uip_ipaddr_t my_ipaddr;

/*---------------------------------------------------------------------------*/
PROCESS(udp_hrpl_process, "app-p2p-root");
AUTOSTART_PROCESSES(&udp_hrpl_process);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(udp_hrpl_process, ev, data)
{
	struct uip_ds6_addr *root_if;
	PROCESS_BEGIN();
	simple_energest_start();
	hrpl_get_global_addr(&my_ipaddr, node_id);
	uip_ds6_addr_add(&my_ipaddr, 0, ADDR_AUTOCONF);
	print_local_addresses();

#if WITH_HRPL
  hrpl_init(1); //hrpl_init(is_root)
#endif /* WITH_HRPL */

	/* The data sink runs with a 100% duty cycle in order to ensure high
	 packet reception rates. */
	NETSTACK_MAC.off(1);
	root_if = uip_ds6_addr_lookup(&my_ipaddr);
	if(root_if != NULL) {
	rpl_dag_t *dag;
	rpl_set_root(RPL_DEFAULT_INSTANCE,&my_ipaddr);
	dag = rpl_get_any_dag();
	rpl_set_prefix(dag, &prefix, 64);
	PRINTF("created a new RPL dag\n");
	} else {
		PRINTF("failed to create a new RPL DAG\n");
	}

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
