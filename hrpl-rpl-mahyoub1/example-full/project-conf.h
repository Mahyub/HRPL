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
 *         configuration file for app-p2p-sim.c to test the HRPL extension
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 */

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#ifndef ROOT_ID
#define ROOT_ID 1
#endif /* ROOT_ID */

#ifndef  WITH_HRPL
#define WITH_HRPL 0
#endif /* WITH_HRPL */

/* Define as minutes */
#undef RPL_CONF_DEFAULT_LIFETIME_UNIT
#define RPL_CONF_DEFAULT_LIFETIME_UNIT   60 //60 default

/* 10 minutes for route's lifetime  */
#undef RPL_CONF_DEFAULT_LIFETIME
#define RPL_CONF_DEFAULT_LIFETIME        10 //30 default

#if WITH_HRPL
#undef HRPL_CONF_MAX_SRC_ROUTE_ENTRIES
#undef HRPL_CONF_MAX_LIFETIME
#undef HRPL_CONF_MAX_SRC_ROUTE_LENGTH
#undef HRPL_CONF_REPLACEMENT_STRATEGY
#undef HRPL_CONF_MAX_LINK_METRIC
#undef HRPL_CONF_MIN_UPDATE_INTERVAL

#define HRPL_CONF_MAX_SRC_ROUTE_ENTRIES 20
#define HRPL_CONF_MAX_LIFETIME RPL_CONF_DEFAULT_LIFETIME * RPL_CONF_DEFAULT_LIFETIME_UNIT  // default 30 * 60
#define HRPL_CONF_MAX_SRC_ROUTE_LENGTH 20
#define HRPL_CONF_REPLACEMENT_STRATEGY NULL_REPLACEMENT_STRATEGY
#define HRPL_CONF_UPDATE_SEND_THRESHOLD 1.5
#define HRPL_CONF_MAX_LINK_METRIC 1024 /* default 1024, Eq ETX of 8 */ /* same as MAX_LINK_METRIC in rpl*/
#define HRPL_CONF_MIN_UPDATE_INTERVAL ((HRPL_CONF_MAX_LIFETIME -100) * (clock_time_t)CLOCK_SECOND)
#endif /* WITH_HRPL */

/*RPL configuration */

#undef RPL_CONF_MOP
#define RPL_CONF_MOP RPL_MOP_STORING_NO_MULTICAST

#undef RPL_NS_CONF_LINK_NUM
#define RPL_NS_CONF_LINK_NUM 0

#undef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES 20

#define RPL_CONF_OF_OCP RPL_OCP_MRHOF // RPL_OCP_OF0 //
/* (DODAGID  present) */
#define RPL_CONF_MAX_DAG_PER_INSTANCE 1
#define RPL_CONF_DAO_SPECIFY_DAG 0
#define RPL_CONF_MAX_INSTANCES    1 // default 1
#define RPL_CONF_STATS 1
/*
 * RPL DAO ACK support. When enabled, DAO ACK will be sent and requested.
 * This will also enable retransmission of DAO when no ack is received. * */
#define RPL_CONF_WITH_DAO_ACK 0

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC contikimac_driver

#undef NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8

#define UIP_CONF_STATISTICS 1
#undef UIP_CONF_TCP
#define UIP_CONF_TCP 0

#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    480

#define TCPIP_CONF_ANNOTATE_TRANSMISSIONS 0 //default 0

#undef CSMA_CONF_MAX_NEIGHBOR_QUEUES
#define  CSMA_CONF_MAX_NEIGHBOR_QUEUES 2//default 2

#endif /* PROJECT_CONF_H_ */
