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
 *         Hybrid RPL (HRPL) extension.
 *
 * HRPL: A Hybrid  IPv6 Routing Protocol for Low-power and Lossy Networks in IoT
 *
 * \author Mohammed Mahyoub <g201405280@kfupm.edu.sa><malmeraby@gmail.com>
 */

#include "hrpl.h"
#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"

#if WITH_HRPL
static struct ctimer periodic_timer;             /* \brief Timer for maintenance of hrpl nodes */

/* Total number of hrpl_nodes (maximum=number of nodes in the network)*/
static int hrpl_num_nodes;

/* Total number of hrpl_nodes (maximum=connections for full mesh network)*/
static int hrpl_num_all_parent;

/* Every known combination of node and its parent in the network */
LIST(hrpl_nodelist);
MEMB(hrpl_nodememb, hrpl_node_t, RPL_NS_LINK_NUM);

MEMB(hrpl_parentsmemb, hrpl_parent_node_t, HRPL_MAX_LINK_NUM);
/*---------------------------------------------------------------------------*/
int
hrpl_get_num_nodes(void)
{
  return hrpl_num_nodes;
}
/*---------------------------------------------------------------------------*/
int
hrpl_get_num_all_parents(void)
{
  return hrpl_num_all_parent;
}
/*---------------------------------------------------------------------------*/
hrpl_node_t *
hrpl_get_node_by_id(uint8_t id)
{
  hrpl_node_t *node = NULL;
  node = list_head(hrpl_nodelist);
  while(node != NULL){
	  if(node->id == id) {
		  return node;
	  }
	  node = list_item_next(node);
  }
  return NULL;
}
/*---------------------------------------------------------------------------*/
hrpl_parent_node_t *
hrpl_get_parent_by_id(hrpl_node_t *child, uint8_t id)
{
	  hrpl_parent_node_t *parent = NULL;
	  if(child == NULL)
		  return NULL;
	  if(child->parent_list == NULL)
		  return NULL;
	  parent = list_head(child->parent_list);
	  while(parent != NULL){
		  if(parent->id == id) {
			  return parent;
		  }
		  parent = list_item_next(parent);
	  }
	  return NULL;
}
/*---------------------------------------------------------------------------*/
hrpl_node_t *
hrpl_add_node(uint8_t id)
{
	hrpl_node_t *child =NULL;
	child = memb_alloc(&hrpl_nodememb);
	/* No space left, abort */
	if(child == NULL) {
	  return NULL;
	}
	LIST_STRUCT_INIT(child, parent_list);
	list_add(hrpl_nodelist, child);
	hrpl_num_nodes++;
	/* Initialize node */
	child->id=id;
	return child;
}
/*---------------------------------------------------------------------------*/
hrpl_parent_node_t *
hrpl_add_parent(hrpl_node_t  *child, uint8_t id)
{
	hrpl_parent_node_t *parent = NULL;
	if(child == NULL) {
	  return NULL;
	}
	parent = memb_alloc(&hrpl_parentsmemb);
	/* No space left, abort */
	if(parent == NULL) {
	  return NULL;
	}
	/* Initialize parent */
	parent->id = id;
	/* add the  parent to the child parent_list */
	list_add(child->parent_list, parent);
	hrpl_num_all_parent++;
	return parent;
}
/*---------------------------------------------------------------------------*/
hrpl_node_t *
hrpl_update_neighbors_metric(rpl_dag_t *dag, const uip_ipaddr_t *child_addr,
		uint8_t neigbour_id, uint16_t link_metric)
{
  uint8_t child_id = child_addr->u8[15];
  uint8_t parent_id = (uint8_t) neigbour_id;
  hrpl_node_t *child = hrpl_get_node_by_id(child_id);
  hrpl_parent_node_t *parent = NULL;

  if(neigbour_id == 0 || child_id == 0 ){
	  PRINTF("HRPL: links_mngr, address of parent or child node is NULL \n");
	  return NULL;
  }
  if(child == NULL) {
	child = hrpl_add_node(child_id);
	if(child  == NULL){
		PRINTF("HRPL: links_mngr, no memory space to add node %u  \n", child_addr->u8[15]);
		return NULL;
	}
  }
	parent = hrpl_get_parent_by_id(child, parent_id);
	if(parent == NULL){
		parent = hrpl_add_parent(child, parent_id);
		if(parent == NULL){
			PRINTF("HRPL: links_mngr, no memory space to add a parent %u\n", neigbour_id);
			return NULL;
		}
	}
	parent->lifetime = HRPL_MAX_LIFETIME;
	parent->link_metric = link_metric;
	PRINTF("HRPL: links_mngr, hrpl_update recv from %u update: [ %u, %u]\n",
				child_addr->u8[15], neigbour_id, link_metric);

	return child;
}
/*---------------------------------------------------------------------------*/

/* Counts no. of parents in specific node's parent_list */
int
hrpl_get_num_parents(hrpl_node_t *node)
{
    int count = 0;  // Initialize count
    hrpl_parent_node_t * parent =list_head(node->parent_list);
    while (parent != NULL)
    {
        count++;
        parent = parent->next;
    }
    return count;
}
/*---------------------------------------------------------------------------*/
void
hrpl_print_parent_list(hrpl_node_t *node)
{
	hrpl_parent_node_t *parent;
	PRINTF("HRPL: links_mngr, parent_list of %u (size= %d) [parent, metric]:{ ",
		  node->id, hrpl_get_num_parents(node));
	for(parent = list_head(node->parent_list); parent != NULL; parent = list_item_next(parent)) {
		PRINTF("[%u, %u] ", parent->id, parent->link_metric );
	}
	PRINTF("}\n");
}
/*---------------------------------------------------------------------------*/
/** Periodic processing on parents */
void
hrpl_handle_nodes_table_periodic_timer(void *ptr){
	hrpl_node_t *node;
	hrpl_parent_node_t *parent;
	for(node = list_head(hrpl_nodelist); node != NULL; node = list_item_next(node)){
		   //pass and decrement lifetime for all nodes with non-infinite lifetime
		for(parent = list_head(node->parent_list); parent != NULL; parent = list_item_next(parent)) {
		    if(parent->lifetime > 0) {
		    	parent->lifetime = parent->lifetime-20;
		    	PRINTF("HRPL: links_mngr, decrement parent %u lifetime  of node %u \n",
		    			parent->id, node->id);
		      // Deallocate the parent with lifetime zero
		      if(parent->lifetime < 1 || parent->link_metric >= HRPL_CONF_MAX_LINK_METRIC) {
		    	  PRINTF("HRPL:  links_mngr, remove the expired parent %u of node %u\n",
		    			  parent->id, node->id);
		    	  list_remove(node->parent_list, parent);
		    	  memb_free(&hrpl_parentsmemb, parent);
		      }
		    }
		}
		if(node->parent_list == NULL ){
			list_remove(hrpl_nodelist, node);
			memb_free(&hrpl_nodememb, node);
	    	PRINTF("HRPL:  links_mngr, remove the expired node %u from the node_list\n", node->id);
			hrpl_num_nodes--;
		}
	}
	  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
hrpl_nodes_table_periodic(void){
	ctimer_set(&periodic_timer, 60 * (clock_time_t)CLOCK_SECOND,
			hrpl_handle_nodes_table_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
void
hrpl_print_all_node_list(void)
{
	hrpl_node_t *node;
	hrpl_parent_node_t *parent;
	PRINTF("HRPL: links_mngr, node_list %d node >>> "
			"{ [nbr0, etx] [nbr1, etx] .. [nbrN, etx] }\n",hrpl_num_nodes);

	for(node = list_head(hrpl_nodelist); node != NULL; node = list_item_next(node)){
		PRINTF("HRPL: node %u >>> { ", node->id);
		for(parent = list_head(node->parent_list); parent != NULL; parent = list_item_next(parent)) {
			PRINTF("[%u, %u] ", parent->id,  parent->link_metric );
		}
		PRINTF("}\n");
	}
	PRINTF("HRPL: End node_list\n");
}
/*---------------------------------------------------------------------------*/
void
hrpl_link_manager_init(void)
{
	hrpl_num_nodes = 0;
	hrpl_num_all_parent = 0;
	memb_init(&hrpl_nodememb);
	list_init(hrpl_nodelist);
	memb_init(&hrpl_parentsmemb);
	hrpl_nodes_table_periodic();
}
/*---------------------------------------------------------------------------*/

#endif /* WITH_HRPL*/
