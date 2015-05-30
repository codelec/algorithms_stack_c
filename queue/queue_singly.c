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
void queue_push(head *h1)
{
	node *temp;
	int data;
	scanf(" %d",&data);
	if (h1->first == NULL)
	{
		h1 -> first = (node*)malloc(sizeof(node));
		h1 -> first -> data = data ;
		h1 -> top = h1 -> first ;
		h1 -> first -> next = NULL;
		printf(" enter queue_push\n");
		return ;
	}
	temp = h1 -> first ;
	h1 -> first = (node*)malloc(sizeof(node));
	h1 -> first -> next = temp;
	h1 -> first -> data = data;
}
void queue_pop(head *h1)
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
		printf("the queue is empty\n");
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
	head_node->first=NULL;
	char ch=getchar();
	while(ch!='q')
	{
		switch(ch)
		{
			case 'p':
				queue_push(head_node);
				break;
			case 'o':
				queue_pop(head_node);
				break;
			default :
				printf("wrong input\n");
		}
		scanf(" %c",&ch);
	}
	return 0;
}