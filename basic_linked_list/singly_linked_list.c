#include <stdio.h>
#include <stdlib.h>
typedef struct node node;
struct node
{
	node* next;
	int data;
	int id;
};
typedef struct
{
	int num_nodes;
	node* first;
}head;
void add_at_end(head*);
void lookup(head*);
void delete(head*);
void sort(head *);
void print_all_nodes(head *);
void insert_at(head *h1);
int main()
{
	head* head_node=(head*)malloc(sizeof(head));
	head_node->num_nodes=0;
	head_node->first=NULL;
	char ch=getchar();
	while(ch!='q')
	{
		switch(ch)
		{
			case 'p':
				print_all_nodes(head_node);
				break;
			case 'a':
				add_at_end(head_node);
				break;
			case 'd':
				delete(head_node);
				break;
			case 'l':
				lookup(head_node);
				break;
			case 's':
				sort(head_node);
				print_all_nodes(head_node);
				break;
			case 'i':
				insert_at(head_node);
				break;
			default :
				printf("wrong input\n");
		}
		scanf(" %c",&ch);
	}
}
void add_at_end(head *h1)
{
	int data;
	node *list;
	scanf(" %d",&data);
	if (h1->first == NULL)
	{
		h1->first=(node*)malloc(sizeof(node));
		(h1->first)->data=data;
		h1->num_nodes += 1;
		(h1->first)->id = (h1->num_nodes) ;
		(h1->first)->next=NULL;
	}
	else
	{
		list=h1->first;
		while( list->next != NULL)
		{
			list = list->next ;
		}
		list -> next = (node*)malloc(sizeof(node));
		list = list->next;
		list -> data = data;
		h1->num_nodes +=1;
		list -> id = (h1->num_nodes);
		printf(" %d",h1->num_nodes);
		list -> next = NULL;
	}
}
void lookup(head *h1)
{
	int data;
	node *list;
	list=h1->first;
	scanf(" %d",&data);
	while(list != NULL)
	{
		if( data == list->data)
		{
			printf(" exist\n");
			return ;
		}
		list=list->next;
	}
	printf(" data does not exist \n");
}
void delete(head *h1)
{
	int data;
	scanf(" %d",&data);
	node *list,*listprev;
	if ((h1->first)->data == data)
	{
		h1->first = h1->first -> next;
		(h1->num_nodes)-=1;
		if (h1->first == NULL)
		{
			printf(" the list is now empty \n");
			return ;
		}
	}
	listprev = h1->first;
	list = listprev -> next ;
	while(list != NULL)
	{
		if ( list -> data == data )
		{
			listprev -> next = list -> next ;
			(h1->num_nodes)-=1;
		}
		if (list -> next != NULL)
		{
			listprev = list ;
			list = list -> next ;
		}
		else 
		{
			return ;
		}
	}
}
void sort(head *h1)
{
	int i,j;
	node *l1,*node1,*node2,*temp;
	node1 = h1 -> first;
	node2 = node1 -> next;
	for (i = h1->num_nodes  ; i > 0; i--)
	{
		for (j = 0; j <= i; ++j)
		{
			if ( node2 -> data > node1 -> data)
			{
				if ( j==0)
				{
					temp = h1 -> first;
					h1 -> first = node1 -> next ;
					node1 -> next = node2 -> next ;
					node2 -> next = temp ;
				}
				else
				{
					temp = l1 -> next ;
					l1 -> next = node1 -> next ;
					node1 -> next = node2 -> next ;
					node2 -> next = temp ;	
				}
			}
			if (node2 -> next == NULL )
			{
				printf(" break \n");
				break;
			}
			l1 = node1 ;
			node1 = node2 ;
			node2 = node2 -> next ;
		}
		node1 = h1 -> first;
		node2 = node1 -> next;	
	}
}
void insert_at(head *h1)
{
	int position,data,count=0;
	scanf(" %d %d",&position,&data);
	node *traverse,*prevtraverse,*temp;
	if ( position == 1)
	{
		temp = h1->first;
		h1->first = (node*)malloc(sizeof(node));
		h1->num_nodes +=1 ;
		h1->first->data = data;
		h1->first->id = h1->num_nodes;
		h1->first->next = temp;
	}
	else
	{
		traverse = h1->first;
		while(position - 2 >= 1)
		{
			traverse=traverse->next;
			position --;
		}
		temp = traverse -> next;
		traverse -> next = (node *)malloc(sizeof(node));
		traverse -> next -> data = data ;
		h1->num_nodes +=1 ;
		traverse -> next -> id = h1 -> num_nodes ;
		traverse -> next -> next = temp ;
	}
}
void print_all_nodes(head *h1)
{
	node *list;
	list=h1->first;
	while(list->next != NULL)
	{
		printf(" %d %d \n",list->data,list->id);
		list=list->next;
	}
	printf(" %d %d \n",list->data,list->id);
}