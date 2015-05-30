#include<stdio.h>
#include<stdlib.h>
#define num_nodes 4
#define max_weight 100
typedef struct struct_list list ;
struct struct_vertex 
{
	short explored;//in the below algorithm node is marked explored iff it has entry in the shortpath array 
	int id;
	list *connected_to;
};
typedef struct struct_vertex vertex;
struct struct_list
{
	int weight;
	vertex *parent;
	vertex *node;
	list *next_connection;
};
vertex node[num_nodes];
int shortpath[num_nodes],num_nodes_explored;
//void print_nodes_in_list(list *head);
void remove_node(list **head,vertex *toremove)
{
	list *traverse,*prev_traverse;
	while((((*head)->weight) >= 0)&&(((*head)->node)->id==(toremove->id)))
	{
		traverse=(*head);
		(*head)=(*head)->next_connection;
		free(traverse);
	}
	prev_traverse=(*head);//stores the addr of the contents being pointed by the current head which is now not the node of interest 
	//prev_traverse is used to store the addr of the parent node(in terms of list)
	traverse=(*head)->next_connection;//points to next node in list
	while((traverse->weight) != -1)//to loop through the rest of the contents of the list to check whether it contains the node of interest or not
	{
		if(((traverse->node)->id)==(toremove->id))
		{
			((prev_traverse)->next_connection)=(traverse->next_connection);
			free(traverse);
			traverse=((prev_traverse)->next_connection);
			continue;//continues to the next iteration to prevent another unnecessary hop
		}
		traverse=(traverse->next_connection);//hop
	}	
}
vertex *find_min_weight_node(list *head)
{
	int min_weight=max_weight;//initializing it with maximum possbile weight stored in the macro
	list *traverse=head;
	vertex *min_weight_node;
	while((traverse->weight) >= 0)//traverse the connected_to
	{
		if ((((traverse->parent)->explored)!=((traverse->node)->explored))&&(((traverse->weight)+shortpath[((traverse->parent)->id)-1]) < min_weight))
		{
			min_weight=(traverse->weight)+shortpath[((traverse->parent)->id)-1];
			min_weight_node=(traverse->node);
		}
		traverse=traverse->next_connection;
	}
	shortpath[(min_weight_node->id)-1]=min_weight;
	(min_weight_node->explored)=1;
	num_nodes_explored++;
	return min_weight_node;
}
void dijkstra(vertex* s)
{
	list *head=(list*)malloc(sizeof(list));//head of the queue
	list *tail,*traverse;
	vertex *min_weight_node=s;
	(s->explored)=1;//to mark start as explored
	num_nodes_explored++;//since one node is now explored
	shortpath[(s->id)-1]=0;
	(head->weight)=-1;
	tail=head;
	while(num_nodes_explored<num_nodes)
	{	
		traverse=(min_weight_node->connected_to);//taverse the list consisting of the nodes connected a particular node at present first in the list
		while(((traverse->weight) >= 0)&&(((traverse->node)->explored)!=1))//traverse the connected_to
		{
			(tail->parent)=min_weight_node;
			(tail->node)=(traverse->node);//adding the traverse node to the queue
			(tail->weight)=(traverse->weight);
			(tail->next_connection)=(list*)malloc(sizeof(list));//tail=(tail->next_connection);//tail being set for the next addition to the queue
			((tail->next_connection)->weight)=-1;
			tail=(tail->next_connection);
			traverse=(traverse->next_connection);
		}
		//print_nodes_in_list(head);
		min_weight_node=find_min_weight_node(head);
		remove_node(&head,min_weight_node);
	}
}
void take_connection()
{
	int from,to,weight;
	list *traverse;
	FILE *fp=fopen("test12","r+");
	while(!feof(fp))
	{
		fscanf(fp," %d %d %d",&from,&to,&weight);
		traverse=node[from-1].connected_to;
		while((traverse->weight) >= 0)
		{
			traverse=(traverse->next_connection);
		}
		(traverse->node)=&node[to-1];
		(traverse->weight)=weight;
		(traverse->next_connection)=(list*)malloc(sizeof(list));
		(traverse->next_connection)->weight=-1;
	}
}
/*void test_connection()
{
	int i;
	list *traverse;
	for (i = 0; i < num_nodes; ++i)
	{
		printf(" %d -> ",node[i].id );
		traverse=node[i].connected_to;
		while((traverse->weight) > 0)
		{
			printf(" %d",(traverse->node)->id);
			traverse=traverse->next_connection;
		}
		printf("\n");
	}
}*/
/*void print_nodes_in_list(list *head)
{
	list *traverse=head;
	while((traverse->weight) >= 0)
	{
		printf(" $%d",(traverse->node)->id);
		traverse=traverse->next_connection;
	}
	printf("\n");
}*/
void initialize()
{
	int i;
	for (i = 0; i < num_nodes; i++)
	{
		(node[i].id)=i+1;
		(node[i].connected_to)=(list*)malloc(sizeof(list));
		((node[i].connected_to)->weight)=-1;
		(node[i].explored)=0;
	}
}
int main()
{
	int i;
	initialize();
	take_connection();
	//test_connection();
	dijkstra(&node[0]);
	for (i = 0; i < num_nodes; ++i)
	{
		printf("%d -> %d\n",i+1,shortpath[i]);
	}
	return 0;
}