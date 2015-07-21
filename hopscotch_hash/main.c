#include <stdlib.h>
#include <stdio.h>
#include "lookup.c"
#include "hopscotch.h"
void intialize()
{
	uint32_t i;
	for (i = 0; i < ADDR_RANGE; ++i)
	{
		segments_arr[0][i].key = -1;
		segments_arr[0][i].data.data = -1;
		segments_arr[0][i]._hop_info = 0;
	}
}
void test()
{
	uint32_t i,j;
	for(i=0;i <= current_max_segment;i++)
	{
		printf("\n %d\t",i);
		for (j = 0; j < ADDR_RANGE; j++)
		{
			if (segments_arr[i][j].key != -1)
				printf("%d\t",bucket_mask & hashlittle(&(segments_arr[i][j].key),sizeof(segments_arr[i][j].key),0));
			else
				printf("-\t");
		}
		printf("\n");
	}
}
int main(int argc, char const *argv[])
{
	char ch;
	uint32_t key;
	DATA data1;
	bool flag = 0;
	intialize();
	do
	{
		ch = getchar();
		switch(ch)
		{
			case 'd':
				scanf(" %d",&key);
				flag = _remove(&key);
				if (flag)
					printf(" removed\n");
				else
					printf(" not there\n");
				break;
			case 'i':
				scanf("%d %d",&key,&(data1.data));
				flag = _add(&key,&data1);
				if (flag)
					printf(" added\n");
				else
					printf(" not added\n");
				test();
				break;
			case 'l':
				scanf(" %d",&key);
				flag = _contains(&key);
				if (flag)
					printf(" present\n");
				else
					printf(" not there\n");
				break;
		}
	}while(ch != 'q');
	return 0;
}