#include <stdio.h>
#include <stdlib.h>
#define NUM_NODES 4
typedef struct list list ;
typedef struct 
{//MORE feature associated with a node can be added here
	short explored;//in the algorithm node is marked explored iff it has entry in the shortpath array 
	int id;
	list *connected_to;
}vertex;
/*the reason why list and list1 have been kept seperate is 
*that list1 will used only when constructing the queue
*used in djikstra in logic_djikstra
*list is used to store the information regarding 
*which nodes are connected to a specific node
*/
struct list
{
	int weight;
 	vertex *node;
	list *next_connection;
};
typedef struct list1 list1;
struct list1
{
	int weight;
	vertex *parent;
	vertex *node;
	list1 *next_connection;
};
//see test12 to knwo how the input is structured
void take_connection(vertex *node)
{
	int from,to,weight;
	list *traverse;
	FILE *fp=fopen("test12","r+");
	while(!feof(fp))
	{
		fscanf(fp," %d %d %d",&from,&to,&weight);
		traverse = node[from - 1].connected_to;
		if (traverse == NULL)
		{
			node[from - 1].connected_to = (list*)malloc(sizeof(list));
			node[from - 1].connected_to->node = &node[to-1]; 
			node[from - 1].connected_to->weight = weight;
			node[from - 1].connected_to->next_connection = NULL;
			continue;
		}
		while(traverse->next_connection != NULL)
		{
			traverse = traverse->next_connection;
		}
		traverse->next_connection = (list*)malloc(sizeof(list));
		traverse = traverse->next_connection;
		traverse->node = &node[to-1];
		traverse->weight = weight;
		traverse->next_connection = NULL;
	}
}
//the following two functions are for debugging pruposes
/* void test_connection(vertex *node)
{
	int i;
	list *traverse;
	for (i = 0; i < NUM_NODES; ++i)
	{
		printf(" %d -> ",node[i].id );
		traverse=node[i].connected_to;
		while(traverse != NULL)
		{
			printf(" %d",(traverse->node)->id);
			traverse=traverse->next_connection;
		}
		printf("\n");
	}
}*/
/*void print_nodes_in_list(list1 *head)
{
	list1 *traverse=head;
	while(traverse != NULL)
	{
		printf(" $%d",(traverse->node)->id);
		traverse=traverse->next_connection;
	}
	printf("\n");
}*/
void initialize(vertex *node,int *shortpath)
{
	int i;
	for (i = 0; i < NUM_NODES; i++)
	{
		(node[i].id) = i + 1;
		shortpath[i] = 0;
		(node[i].connected_to) = NULL;
		(node[i].explored) = 0;
	}
}
#include "logic_djikstra.c"
int main()
{
	int i,shortpath[NUM_NODES];
	vertex node[NUM_NODES];
	initialize(node,shortpath);
	take_connection(node);
	//test_connection(node);
	dijkstra(&node[0],shortpath);
	for (i = 0; i < NUM_NODES; ++i)
	{
		printf("%d -> %d\n",i + 1,shortpath[i]);
	}
	return 0;
}