#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct struct_list list ;
typedef struct 
{
	short explored;
	int id;
	int level;
	list *connected_to;
}vertex;
struct struct_list
{
	vertex *node;
	list *next_connection;
};
#include "logic_bfs.c"
int main(int argc, char const *argv[])
{
	int i=0,a=0,k=0,b=0,index=0;
	vertex node[6]={0};
	for (i=0;i<10;i++)
	{
		(node[i]).id=i+1;
	}
	char ch,line[20]="";
	FILE *fp=fopen("testfile","r+");//file to be opened with the pointer at the start of the file
	list *next=(list*)malloc(sizeof(list));
	ch=fgetc(fp);//extracts character from file 
	while(!feof(fp)) // feof returns true on end of file
	{
		if (ch == '\n')//to start taking connections of another vertex 
		{//initialize some of the variables since the next iteration of "while" will work on the next line of input
			(next->node)=NULL;
			k=0,a=0,index=0;
		}
		else if (ch != ' ')//<space> accumulate till the space is detected since one number(not digit)
		{		
			line[index++]=ch;		
		}
		else
		{
			b=atoi(line)-1;//convert string to int
			if (k==0)
			{
				a=atoi(line) - 1;//index starts from zero
				(node[a]).id=a+1;
			}
			else if (k==1)
			{
				(node[a]).connected_to=(list*)malloc(sizeof(list));
				(node[b]).id=b+1;
				((node[a]).connected_to)->node=&node[b];//point to one of the nodes it is connected to .. which is specified first in the input by the use	
				((node[a]).connected_to)->next_connection=(list*)malloc(sizeof(list));//since it is a list provide space to the next node in the list (where the node is none but the next vertex node[a] is connected to)
				next=((node[a]).connected_to)->next_connection;//next points to next node in the list
			}
			else
			{//continue the list work
				next->node=&node[b];
				(node[b]).id=b+1;
				next->next_connection=(list*)malloc(sizeof(list));
				next=next->next_connection;
			}
			char line[20]="";
			k++;//count of which number of the current line is being processed on
			index=0;
		}
		ch=fgetc(fp);
	}
	bfs(&node[1]);//node from where the leveling is to be calculated
	for ( i = 0; i < 6; ++i)
	{
		printf("%d -> %d\n",node[i].id,node[i].level);
	}
}