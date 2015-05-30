#include<stdio.h>
#include<stdlib.h>
typedef struct node node;
struct node
{
	node *next;
	int data;
};
typedef struct
{
	node *first;
	node *top;
}head;
void stack_push(head *h1)
{
	int data;
	scanf(" %d",&data);
	if (h1->first == NULL)
	{
		h1 -> first = (node*)malloc(sizeof(node));
		h1 -> first -> data = data ;
		h1 -> top = h1 -> first ;
		h1 -> first -> next = NULL;
		printf(" enter stack_push\n");
		return ;
	}
	h1 -> top -> next = (node*)malloc(sizeof(node));
	h1 -> top -> next -> data = data;
	h1 -> top -> next -> next = NULL;
	h1 -> top = h1 -> top -> next;
}
void stack_pop(head *h1)
{
	if (h1 -> top != h1 -> first)
	{
		node *traverse = h1 -> first;
		while(traverse -> next != h1 -> top)
		{
			traverse = traverse -> next ;
		}
		printf(" %d\n",h1 -> top-> data);
		free(h1->top);
		h1 -> top = traverse;
		traverse -> next =  NULL;		
	}
	else if (h1 -> first == NULL)
	{
		printf("the stack is empty\n");
		return ;
	}
	else
	{
		printf("%d\n", h1 -> first -> data);
		free(h1 -> first);
		//free(h1 -> top);
		h1 -> first = NULL ;
		h1 -> top = NULL ;
	}
}
int main(int argc, char const *argv[])
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
				stack_push(head_node);
				break;
			case 'o':
				stack_pop(head_node);
				break;
			default :
				printf("wrong input\n");
		}
		scanf(" %c",&ch);
	}
	return 0;
}