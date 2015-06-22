#include<stdio.h>
#include<stdlib.h>
#define num_nodes 875714
typedef struct struct_list list ;
typedef struct 
{
	short explored;
	int id;
	int leader_id;
	list* connected_to;
}vertex;
struct struct_list
{
	vertex* node;
	list* next_connection;
};
int a1,a2,a3,a4,a5;//to store the top 4 number of scc's
vertex node[num_nodes];
void take_connection(short);//direction = 1 for normal graph ... direction = 2 for reverse graph
void initialize();//initializes the nodes after a dfs loop call
#include "logic_scc.h"
int main(int argc, char const *argv[])
{
	initialize(); 
	take_connection(2);
	dfs_loop(2);
	initialize();
	take_connection(1);
	dfs_loop(1);
	printf("%d %d %d %d %d\n",a1,a2,a3,a4,a5);
	return 0;
}
void initialize()
{
	int i;
	for (i = 0; i < num_nodes; i++)
	{
		node[i].id=i+1;
		(node[i].connected_to)=(list*)malloc(sizeof(list));
		(node[i].connected_to)->node=(vertex*)NULL;
		node[i].explored=0;
	}
}
void take_connection(short direction)
{
	int from , to;
	list *traverse;
	FILE *fp=fopen("SCC.txt","r+");
	while(!feof(fp))
	{
		if (direction==2)//since the graph with reverse connections has tp be generated
		{
			fscanf(fp,"%d %d",&to,&from);
		}
		else
		{
			fscanf(fp,"%d %d",&from,&to);
		}
		traverse=node[from-1].connected_to;
		while((traverse->node) != (vertex*)NULL)
		{
			traverse=(traverse->next_connection);
		}
		(traverse->node)=&node[to-1];
		(traverse->next_connection)=(list*)malloc(sizeof(list));
		(traverse->next_connection)->node=(vertex*)NULL;
	}
}