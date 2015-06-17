#include<stdio.h>
#include<stdlib.h>
#define num_nodes 875714
typedef struct struct_list list ;
struct struct_vertex 
{
	short explored;
	int id;
	int leader_id;
	list* connected_to;
};
typedef struct struct_vertex vertex;
struct struct_list
{
	vertex* node;
	list* next_connection;
};
int a1,a2,a3,a4,a5;//to store the top 4 number of scc's
int count=0;//to keep a track of the number of connected components during dfs loop
vertex node[num_nodes];
int order_id[num_nodes]={0};//stores the id of the nodes in the required order
vertex *s;//keeps a record of the node from where the last dfs call was from
int t=0;//increments after a node is completely done with in a particular dfs loop call
void take_connection(short);//direction = 1 for normal graph ... direction = 2 for reverse graph
void initialize();//initializes the nodes after a dfs loop call
void dfs(vertex*,int);//int call_type = 1 for the second call = 2 for the first call
void dfs_loop(int);//int call_type = 1 for the second call = 2 for the first call
void isitintop4(int n);
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
void dfs_loop(int call_type)
{
	int i;
	for (i = num_nodes - 1; i >= 0; i--)
	{
		if (call_type==2)
		{
			if (node[i].explored!=1)
			{
				dfs(&node[i],call_type);
			}
		}
		else if(call_type == 1)
		{
			if (node[order_id[i]-1].explored!=1)
			{
				s=&node[order_id[i]-1];
				(s->explored)=1;
				dfs(&node[order_id[i]-1],call_type);
				isitintop4(count);
				count=0;
			}
		}
	}
}
void dfs(vertex* dfs_s,int call_type)
{
	(dfs_s->explored)=1;
	list* traverse;	
	traverse=dfs_s->connected_to;//taverse the list consisting of the nodes connected a particular node at present first in the list
	if (call_type == 1)
	{
		count++;
		dfs_s->leader_id=s->id;
	}
	while((traverse->node) != (vertex*)NULL)//traverse the connected_to
	{
		if (((traverse->node)->explored)!=1)
		{
			((traverse->node)->explored)=1;//marking the node just added to the queue as exlpored
			dfs(traverse->node,call_type);
		}
		traverse=traverse->next_connection;
	}
	if (call_type == 2)
	{
		order_id[t++]=(dfs_s->id);
	}
}
void isitintop4(int n)
{
	if(n>a1)
	{
		a5=a4,a4=a3,a3=a2,a2=a1,a1=n;
	}
	else if (n>a2)
	{
		a5=a4,a4=a3,a3=a2,a2=n;	
	}
	else if (n>a3)
	{
		a5=a4,a4=a3,a3=n;
	}
	else if (n>a4)
	{
		a5=a4,a4=n;
	}
	else if (n>a5)
	{
		a5=n;
	}
}