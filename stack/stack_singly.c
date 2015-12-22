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
void stack_push(head *h1, void *to_add)
{
	if (h1->first == NULL)
	{
		h1 -> first = to_add;
		h1 -> top = h1 -> first ;
		h1 -> first -> next = NULL;
		return ;
	}
	h1 -> top -> next = to_add;
	h1 -> top -> next -> next = NULL;
	h1 -> top = h1 -> top -> next;
}
void* stack_pop(head *h1)
{
	node *temp;
	if (h1 -> top != h1 -> first)
	{
		node *traverse = h1 -> first;
		while(traverse -> next != h1 -> top)
			traverse = traverse -> next ;
		temp = h1 -> top;
		h1 -> top = traverse;
		traverse -> next =  NULL;
		return temp;	
	}
	else if(h1 -> top == h1 -> first){
		temp = h1 -> top ;
		h1 -> top = NULL;
		h1 -> first = NULL;
		return temp;
	}
	else 
		return NULL;
}
int main(int argc, char const *argv[])
{
	head* head_node=(head*)malloc(sizeof(head));
	head_node->first=NULL;
	char ch=getchar();
	int data;
	node *temp;
	while(ch!='q')
	{
		switch(ch)
		{
			case 'p':
				scanf(" %d",&data);
				temp = malloc(sizeof(node));
				temp -> data = data;
				stack_push(head_node,temp);
				break;
			case 'o':
				temp = stack_pop(head_node);
				if (temp != NULL)
					printf("%d\n",((node *)temp) -> data);
				else printf("stack empty\n");
				free(temp);
				break;
			default :
				printf("wrong input\n");
		}
		scanf(" %c",&ch);
	}
	return 0;
}