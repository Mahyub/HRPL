/*
 * Copyright (c) 2015, Swedish Institute of Computer Science.
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
 */

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#define UP_ONLY 0 //In case of app-up-only-mahyoub
#undef RPL_CONF_MOP
#if UP_ONLY
#define RPL_CONF_MOP RPL_MOP_NO_DOWNWARD_ROUTES
#else
#define RPL_CONF_MOP RPL_MOP_NON_STORING // RPL_MOP_STORING_NO_MULTICAST //
#endif

#define WITH_HRPL 0 /* Set this to run with HRPL and non-storing mode */


#undef NBR_TABLE_CONF_MAX_NEIGHBORS
#undef UIP_CONF_MAX_ROUTES

#ifdef TEST_MORE_ROUTES
/* configure number of neighbors and routes */
#define NBR_TABLE_CONF_MAX_NEIGHBORS     30
#define UIP_CONF_MAX_ROUTES   30
#else
/* configure number of neighbors and routes */
#define NBR_TABLE_CONF_MAX_NEIGHBORS     30
#define UIP_CONF_MAX_ROUTES   30
#endif /* TEST_MORE_ROUTES */

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC   contikimac_driver  //nullrdc_driver
#undef NULLRDC_CONF_802154_AUTOACK
#define NULLRDC_CONF_802154_AUTOACK       1

/* Define as minutes */
#define RPL_CONF_DEFAULT_LIFETIME_UNIT   60

/* 10 minutes lifetime of routes */
#define RPL_CONF_DEFAULT_LIFETIME        10

#define RPL_CONF_DEFAULT_ROUTE_INFINITE_LIFETIME 1

/*from orpl*/
/*#define UIP_CONF_DS6_ADDR_NBU 1

//#define RPL_CONF_DIO_INTERVAL_MIN 12  // default 12
//#define RPL_CONF_DIO_INTERVAL_DOUBLINGS 8 // default 8
#define RPL_CONF_DIO_INTERVAL_MIN 12  // default 12
#define RPL_CONF_DIO_INTERVAL_DOUBLINGS 8 // default 8
#define RPL_CONF_DIO_REDUNDANCY   200  // default 10

#define RPL_CONF_MAX_INSTANCES    1 // default 1
#define RPL_CONF_MAX_DAG_PER_INSTANCE 1 // default 2

/// Other system parameters //

#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    160

#undef UIP_CONF_UDP_CONNS
#define UIP_CONF_UDP_CONNS       2

#undef UIP_CONF_FWCACHE_SIZE
#define UIP_CONF_FWCACHE_SIZE    4

#undef UIP_CONF_TCP
#define UIP_CONF_TCP                    0

#undef UIP_CONF_UDP_CHECKSUMS
#define UIP_CONF_UDP_CHECKSUMS   0

#undef SICSLOWPAN_CONF_FRAG
#define SICSLOWPAN_CONF_FRAG 0

#undef DCOSYNCH_CONF_ENABLED
#define DCOSYNCH_CONF_ENABLED 0

#undef RF_CHANNEL
#define RF_CHANNEL              15

#define RF_POWER                31


#undef CSMA_CONF_MAX_NEIGHBOR_QUEUES
#define CSMA_CONF_MAX_NEIGHBOR_QUEUES 4

#undef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM 4
#define UIP_CONF_DS6_ROUTE_NBU  70
#define NEIGHBOR_CONF_MAX_NEIGHBORS 16
#define UIP_CONF_DS6_NBR_NBU  16
#define RPL_CONF_MAX_PARENTS_PER_DAG 16   */

#endif
