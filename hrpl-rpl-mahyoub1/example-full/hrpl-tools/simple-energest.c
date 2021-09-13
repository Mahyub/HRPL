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
#include "contiki.h"
#include "simple-energest.h"
#include <stdio.h>
#include "hrpl-tools.h"

unsigned long  all_cpu, all_lpm, all_tx, all_rx;

PROCESS(simple_energest_process, "Simple Energest");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(simple_energest_process, ev, data)
{
  static struct etimer periodic;
  PROCESS_BEGIN();
  etimer_set(&periodic, 3 *60 * CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_UNTIL(etimer_expired(&periodic));
    etimer_reset(&periodic);
    rpl_stats_print();
    simple_energest_print();
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void simple_energest_start() {
  energest_flush();
  all_tx = energest_type_time(ENERGEST_TYPE_TRANSMIT);
  all_rx = energest_type_time(ENERGEST_TYPE_LISTEN);
  all_cpu = energest_type_time(ENERGEST_TYPE_CPU);
  all_lpm=energest_type_time(ENERGEST_TYPE_LPM);
  process_start(&simple_energest_process, NULL);
}

/*---------------------------------------------------------------------------*/
void simple_energest_print() {
  energest_flush();

  all_cpu = energest_type_time(ENERGEST_TYPE_CPU) ;
  all_lpm=energest_type_time(ENERGEST_TYPE_LPM);
  all_rx = energest_type_time(ENERGEST_TYPE_LISTEN);
  all_tx = energest_type_time(ENERGEST_TYPE_TRANSMIT);
  HRPL_LOG("energy:  %lu  %lu  %lu  %lu\n",all_cpu,all_lpm,all_rx,all_tx);
}

