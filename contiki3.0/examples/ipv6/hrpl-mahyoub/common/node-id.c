/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
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

/**
 * \file
 *         Utility to store a node id in the external flash
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "sys/node-id.h"
#include "net/ip/uip.h"
#include "contiki-conf.h"
#include "dev/xmem.h"
#include "net/linkaddr.h"
#include "net/ipv6/uip-ds6.h"
#include "random.h"

unsigned short node_id = 0;

struct id_mac {
  uint16_t id;
  uint16_t mac;
};

static const uint16_t any_to_any_list[] = {  1, 2, 4, 6, 8, 10, 12, 14, 15, };




#define N_NODES 15

uint16_t node_id_from_rimeaddr(const linkaddr_t *addr) {
  if(addr == NULL) return 0;
  else return addr->u8[7];
}


uint16_t node_id_from_lipaddr(const uip_ipaddr_t *addr) {
  return (addr->u8[14] << 8) + addr->u8[15];
//  uip_ds6_nbr_t *nbr = uip_ds6_nbr_lookup(addr);
//  if(nbr) return node_id_from_rimeaddr(&nbr->lladdr);
//  else return 0;
}

uint16_t node_id_from_ipaddr(const uip_ipaddr_t *addr) {
  return (addr->u8[14] << 8) + addr->u8[15];
}

void node_id_restore() {
  printf("node_id_restore %u %u\n", node_id, node_id_from_rimeaddr(&linkaddr_node_addr));
  node_id = node_id_from_rimeaddr(&linkaddr_node_addr);
}

uint16_t get_id(uint16_t index) {

  return index;
}

uint16_t get_n_nodes() {
  return N_NODES;
}

uint16_t get_node_id(uint16_t index) {

  return 1 + (index % N_NODES);

}

uint16_t get_random_id() {

  return 1 + ((uint16_t)random_rand()) % N_NODES;
}

int id_has_outage(uint16_t id) {
  return id % 4 == 1;
}

int has_outage(void) {
  return id_has_outage(node_id);
}

int is_id_addressable(uint16_t id) {
#if (ALL_NODES_ADDRESSABLE == 0)
  return id % 2 == 0;
#else
  return 1;
#endif
}

int is_addressable() {
  return is_id_addressable(node_id);
}

int is_id_in_any_to_any(uint16_t id) {
  const uint16_t *curr = any_to_any_list;
  while(*curr != 0) {
    if(*curr == id) {
      return 1;
    }
    curr++;
  }
  return 0;
}

int is_in_any_to_any() {
  return is_id_in_any_to_any(node_id);
}
