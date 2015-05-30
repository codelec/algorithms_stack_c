#include<stdio.h>
#include<stdlib.h>
typedef struct node node;
struct node
{
	node *next;
	node *prev;
	int data;
	int id;
};
typedef struct
{
	int num_nodes;
	node *first;
}head;
void add_at_end(head*);
void lookup(head*);
void delete(head*);
void print_all_nodes(head*);
void insert_at(head*);
void sort(head *);
int main(int argc, char const *argv[])
{
	head *head_node = (head *)malloc(sizeof(head));
	head_node -> num_nodes = 0;
	head_node -> first = NULL;
	char ch = getchar();
	while(ch!='q')
	{
		switch(ch)
		{
			case 'a':
				add_at_end(head_node);
				break;
			case 'd':
				delete(head_node);
				break;
			case 'l':
				lookup(head_node);
				break;
			case 'p':
				print_all_nodes(head_node);
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
	return 0;
}
void add_at_end(head *h1)
{
	int data;
	node *traverse;
	scanf(" %d",&data);
	if (h1 -> first == NULL)
	{
		h1 -> first = (node*)malloc(sizeof(node));
		(h1 -> first) -> data = data;
		h1 -> num_nodes += 1;
		(h1 -> first) -> id = (h1 -> num_nodes) ;
		(h1 -> first) -> next = NULL;
		(h1 -> first) -> prev = NULL;
	}
	else
	{
		traverse = h1 -> first;
		while( traverse -> next != NULL)
		{
			traverse = traverse -> next ;
		}
		traverse -> next = (node*)malloc(sizeof(node));
		traverse -> next -> data = data;
		h1 -> num_nodes += 1;
		traverse -> next -> id = (h1->num_nodes);
		printf(" %d",h1->num_nodes);
		traverse -> next -> next = NULL;
		traverse -> next -> prev = traverse ;
	}
}
void delete(head *h1)
{
	int data ;
	scanf(" %d",&data);
	if (h1 -> first -> data == data)
	{
		h1 -> first = h1 -> first -> next ;
		h1 -> first -> prev = NULL;
	}
	node *traverse;
	traverse = h1 -> first;
	while(traverse->next != NULL)
	{
		if (traverse -> data == data)
		{
			traverse -> prev -> next = traverse -> next ;
			traverse -> next -> prev = traverse -> prev ;
		}
		traverse = traverse -> next;
	}	
	if (traverse -> data == data)
	{
		traverse -> prev -> next = NULL ;
	}
}
void lookup(head *h1)
{
	node *traverse;
	traverse = h1 -> first;
	int data;
	scanf(" %d",&data);
	while(traverse != NULL)
	{
		if (traverse -> data == data)
		{
			printf(" exist \n");
			return ;
		}
		traverse = traverse -> next;
	}	
}
void print_all_nodes(head *h1)
{
	node *traverse;
	traverse = h1 -> first;
	while(traverse -> next != NULL)
	{
		printf(" %d %d \n",traverse -> data,traverse -> id);
		traverse = traverse -> next;
	}
	printf(" %d %d \n",traverse -> data,traverse -> id);
}
void insert_at(head *h1)
{
	int position,data;
	scanf(" %d %d",&position,&data);
	node *traverse,*prevtraverse,*temp;
	if ( position == 1)
	{
		temp = h1 -> first;
		h1 -> first = (node*)malloc(sizeof(node));
		h1 -> first -> prev = NULL ;
		h1 -> first -> next = temp ;
		h1 -> num_nodes += 1 ;
		h1 -> first -> data = data;
		h1 -> first -> id = h1->num_nodes;
		h1 -> first -> next -> prev = h1 -> first ;
	}
	else
	{
		traverse = h1->first;
		while(position - 2 >= 1)
		{
			traverse=traverse->next;
			position --;
		}
		if (traverse -> next != NULL)
		{
			temp = traverse -> next;
			traverse -> next = (node *)malloc(sizeof(node));
			traverse -> next -> data = data ;
			h1 -> num_nodes +=1 ;
			traverse -> next -> id = h1 -> num_nodes ;
			traverse -> next -> next = temp ;
			traverse -> next -> next -> prev = traverse -> next;
			traverse -> next -> prev = traverse ; 	
		}
		else
		{
			traverse -> next = (node*)malloc(sizeof(node));
			traverse -> next -> data = data ;
			traverse -> next -> prev = traverse -> next;
			traverse -> next -> next = NULL;
		}
	}
}
void sort(head *h1)
{
	int i,j;
	node *node1,*node2;
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
					h1 -> first = node2 ;
					node1 -> prev = node2;
					node1 -> next = node2 -> next;
					node2 -> next -> prev = node1;
					node2 -> next = node1;
					node2 -> prev = NULL ;
				}
				else
				{
					node2 -> prev = node1 -> prev ;
					node1 -> next = node2 -> next ;
					node1 -> prev -> next = node2;
					node2 -> next -> prev = node1;
					node2 -> next = node1;
					node1 -> prev = node2;	
				}
			}
			if (node2 -> next == NULL )
			{
				break;
			}
			node1 = node2 ;
			node2 = node2 -> next ;
		}
		node1 = h1 -> first;
		node2 = node1 -> next;	
	}
}