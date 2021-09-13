

 /* hrpl-rt-mngr.c
 *program for Dijkstra's shortest path algorithm for adjacency
 *list representation of graph
 *  Created on: Nov 20, 2018
 *      Author: Mohammed Mahyoub <g201405280@kfupm.edu.sa><malmeraby@gmail.com>*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "net/rpl/hrpl.h"
#include "lib/memb.h"
//#if WITH_HRPL
#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

/* Structure to represent a min heap node*/
struct MinHeapNode
{
	int v;
	int dist;
};

/* Structure to represent a min heap*/
struct MinHeap
{
	int size;	 // Number of heap nodes present currently
	int capacity; // Capacity of min heap
	int *pos;	 // This is needed for decreaseKey()
	struct MinHeapNode **array;
};
/*---------------------------------------------------------------------------*/
/* A utility function to create a new Min Heap Node */
static struct MinHeapNode* newMinHeapNode(int v, int dist)
{
	struct MinHeapNode* minHeapNode =
		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

/*---------------------------------------------------------------------------*/
/* A utility function to create a Min Heap */
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*) malloc(sizeof(struct MinHeap));
	if(minHeap!= NULL){
		printf("The minHeap is created successfully\n");
	} else{
		printf("The minHeap is not created, No memory space\n");

	}
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

/*---------------------------------------------------------------------------*/
/* A utility function to swap two nodes of min heap. Needed for min heapify */
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

/*---------------------------------------------------------------------------*/
/* A standard function to heapify at given idx
  *This function also updates position of nodes when they are swapped.
  *Position is needed for decreaseKey()*/
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist < minHeap->array[smallest]->dist )
	smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist < minHeap->array[smallest]->dist )
	smallest = right;

	if (smallest != idx)
	{
		// The nodes to be swapped in min heap
		struct MinHeapNode *smallestNode = minHeap->array[smallest];
		struct MinHeapNode *idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

/*---------------------------------------------------------------------------*/
/* A utility function to check if the given minHeap is ampty or not*/
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}
/*---------------------------------------------------------------------------*/

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	/* Store the root node*/
	struct MinHeapNode* root = minHeap->array[0];

	/* Replace root node with last node*/
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	/* Update position of last node*/
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	/* Reduce heap size and heapify root*/
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

/*---------------------------------------------------------------------------*/
/* Function to decreasy dist value of a given vertex v. This function
 * uses pos[] of min heap to get the current index of node in min heap*/
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
	/* Get the index of v in heap array*/
	int i = minHeap->pos[v];

	/* Get the node and update its dist value*/
	minHeap->array[i]->dist = dist;

	/* Travel up while the complete tree is not hepified This is a O(LogN) loop*/

	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
	{
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		/* move to parent index*/
		i = (i - 1) / 2;
	}
}

/*---------------------------------------------------------------------------*/
/* A utility function to check if a given vertex  'v' is in min heap or not*/
int isInMinHeap(struct MinHeap *minHeap, int v)
{
if (minHeap->pos[v] < minHeap->size){
	return 1;
	} else{
		return 0;
	}
}

/*---------------------------------------------------------------------------*/
/* A utility function used to print the solution */
/*void hrpl_rt_mangr_print_path_cost(uint16_t dist[], int n)
{
	int i;
	printf("Vertex Distance from Source %d\n");
	for (i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}*/

/*---------------------------------------------------------------------------*/

/* The main function that calculates distances of shortest paths from src to all
   * vertices. It is a O(E*LogV) function. src or target are the hrpl_node->id */
void hrpl_rt_mangr_dijkstra(int src, int target)
{
	uint16_t *dist = NULL; //pointer to integer
	int nodes_num;
	nodes_num= N_NODES+1; /* Get the number of vertices in graph*/
	dist = (uint16_t *)malloc(nodes_num * sizeof(uint16_t));
	if(dist==NULL){
		PRINTF("hrpl-rt-mngr.c the dist array can't be allocated\n");
		return;
	}
	//uint16_t dist[nodes_num];	 /* dist values used to pick minimum weight edge in cut*/
	/* minHeap represents set E */
	struct MinHeap* minHeap = createMinHeap(nodes_num);

	/* Initialize min heap with all vertices. dist value of all vertices */
	int v;
	for (v = 0; v < nodes_num; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	/* Make dist value of src vertex as 0 so that it is extracted first */
/*	minHeap->array[src] = newMinHeapNode(src, dist[src]);*/
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	/* Initially size of min heap is equal to V */
	minHeap->size = nodes_num;

	/* In the following loop, min heap contains all nodes whose shortest distance is not yet finalized */
	while (!isEmpty(minHeap))
	{
		/* Extract the vertex with minimum distance value*/
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; // Store the extracted vertex number
		if(u==target){
			printf("HRPL the target was found\n");
			break;
		}
		/* Traverse through all adjacent vertices of u (the extracted vertex) and update their distance values*/
		hrpl_parent_node_t* parent = list_head(hrpl_get_node_by_id((uint8_t)u)->parent_list);
		while (parent != NULL)
		{
			int v = parent->id;

			/* If shortest distance to v is not finalized yet, and distance to v
			* through u is less than its previously calculated distance */
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
					parent->link_metric + dist[u] < dist[v])
			{
				dist[v] = dist[u] + parent->link_metric;

				/* update distance value in min heap also*/
				decreaseKey(minHeap, v, dist[v]);
			}
			parent = list_item_next(parent);
		}
	}

	/*print the calculated shortest distances*/
	printf("Vertex Distance from Source..\n");
	int i=0;
	for (i = 0; i < nodes_num; ++i){
		printf("%d \t\t %d\n", i, dist[i]);
	}
	int k;
	for (k = 0; k < nodes_num; ++k)
	{
		free(minHeap->array[k]);
	}
	free(v);
	free(i);
	free(k);
	free(minHeap->pos);
	free(minHeap->array);
	free(minHeap);
	free(dist);
}
/*---------------------------------------------------------------------------*/

//#endif /* WITH_HRPL */

