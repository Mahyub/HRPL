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
 *         Header file for hrpl-log.c, and a set of macros for HRPL logging
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 */

#ifndef HRPL_TOOLS_H
#define HRPL_TOOLS_H

#include "ip/uip.h"
extern uip_ipaddr_t prefix;
/* Used to identify packets carrying HRPL log */
#define HRPL_LOG_MAGIC 0xcafebabe

/* Data structure copied at the end of all data packets, making it possible
 * to trace packets at every hop, from every layer. */
struct app_data {
  uint32_t magic;
  uint32_t seqno;
  uint16_t src;
  uint16_t dest;
  uint8_t hop;
  uint8_t sugg_etx;
  uint8_t actual_etx;
};

void hrpl_get_global_addr(uip_ipaddr_t *addr, uint16_t id);
void print_local_addresses(void);
/* Copy an appdata to another with no assumption that the addresses are aligned */
void app_copy_data(struct app_data *dst, struct app_data *src);/* Get dataptr from the packet currently in uIP buffer */
struct app_data *appdataptr_from_uip();
/* Get dataptr from the current packetbuf */
struct app_data *appdataptr_from_packetbuf();
/* Log information about a data packet along with HRPL routing information */
void log_appdataptr(struct app_data *dataptr);
/* Log information about a uip layers statistics */
void uip_statistics_print();
void rpl_stats_print();
int is_id_in_sending_list(uint16_t id);
int is_id_in_receiving_list(uint16_t id);
#define HRPL_LOG(...) printf(__VA_ARGS__)
//#define HRPL_LOG(...)
#define HRPL_LOG_FROM_PACKETBUF log_appdataptr(appdataptr_from_packetbuf())
#define HRPL_LOG_INC_HOPCOUNT_FROM_PACKETBUF() { struct app_data *ptr = appdataptr_from_packetbuf(); if(ptr) ptr->hop++; }
#define HRPL_LOG_INC_ETXCOUNT_FROM_PACKETBUF() { struct app_data *ptr = appdataptr_from_packetbuf(); if(ptr) ptr->actual_etx++; }
#endif /* HRPL_TOOLS_H */
