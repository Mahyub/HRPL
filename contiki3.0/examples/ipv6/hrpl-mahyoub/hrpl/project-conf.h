#ifndef __PROJECT_CONF_H__
#define __PROJECT_CONF_H__

#define UP_ONLY 0
#define ALL_NODES_ADDRESSABLE 0
#define WITH_HRPL 0

/* Number of non storing nodes stored at the root*/
#undef RPL_NS_CONF_LINK_NUM
#define RPL_NS_CONF_LINK_NUM 50


#undef RPL_CONF_MOP
#define RPL_CONF_MOP RPL_MOP_STORING_NO_MULTICAST //RPL_MOP_NON_STORING  //

#define RPL_CONF_OF_OCP RPL_OCP_MRHOF

/* RPL and neighborhood information */

#define RPL_CONF_INIT_LINK_METRIC 6 /* default 5 */

#define RPL_CONF_MAX_DAG_PER_INSTANCE 1


/*
 Reject parents that have a higher link metric than the following.
#define MAX_LINK_METRIC     10
*/
/* if RPL_CONF_WITH_MC is enabled then the parent will multicast its total etx
 * ( agregated etx to the root)  within the DIO message. So the childern will use this etx to calculate
 * their rank instead of using the parent rank with is also included in the same  DIO */
#define RPL_CONF_WITH_MC 0  //if this set to 1 then the next line will be enabled
#define RPL_CONF_DAG_MC RPL_DAG_MC_ETX //RPL_DAG_MC_ENERGY

#define LINK_STATS_CONF_INIT_ETX(stats) guess_etx_from_rssi(stats)

/* Delay between reception of a no-path DAO and actual route removal */
#define RPL_CONF_NOPATH_REMOVAL_DELAY 60 //default 60

/* (DODAGID  present) */
#define RPL_CONF_DAO_SPECIFY_DAG 1
/*
 * RPL DAO ACK support. When enabled, DAO ACK will be sent and requested.
 * This will also enable retransmission of DAO when no ack is received. * */
#define RPL_CONF_WITH_DAO_ACK 1

#define  RPL_CONF_WITH_PROBING 1
#define  RPL_CONF_PROBING_INTERVAL    (5 * CLOCK_SECOND)

#undef NEIGHBOR_CONF_MAX_NEIGHBORS
#undef UIP_CONF_DS6_NBR_NBU
#undef RPL_CONF_MAX_PARENTS_PER_DAG


#define NEIGHBOR_CONF_MAX_NEIGHBORS 16
#define UIP_CONF_DS6_NBR_NBU  16
#define RPL_CONF_MAX_PARENTS_PER_DAG 16

#undef UIP_CONF_DS6_ROUTE_NBU
#define UIP_CONF_DS6_ROUTE_NBU  70

#define UIP_CONF_DS6_LL_NUD 1 /* WITH_HRPL */
#define UIP_CONF_ND6_SEND_NS 1 /* WITH_HRPL */


//#define UIP_CONF_ND6_REACHABLE_TIME  5000 /* default 30000*/
//#define UIP_CONF_ND6_MAX_UNICAST_SOLICIT 3 /*default 3*/
/* Other system parameters */

/*
#undef WITH_PHASE_OPTIMIZATION
#define WITH_PHASE_OPTIMIZATION CMD_PHASE_LOCK
*/

#undef CC2420_CONF_SFD_TIMESTAMPS
#define CC2420_CONF_SFD_TIMESTAMPS 0

#undef SICSLOWPAN_CONF_MAX_MAC_TRANSMISSIONS
#define SICSLOWPAN_CONF_MAX_MAC_TRANSMISSIONS   5

#define MIN_DIO_RECEIVED 3

#endif /* __PROJECT_CONF_H__ */
