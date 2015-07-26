#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void test();
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
		printf("\n %u- \t",i);
		for (j = 0; j < ADDR_RANGE; j++)
		{
			if (segments_arr[i][j].key != -1)
				printf("%u\t",bucket_mask & hashlittle(&(segments_arr[i][j].key),sizeof(segments_arr[i][j].key),hash_init_val));
			else
				printf("-\t");
		}
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	clock_t begin,end,during;
	begin = clock();
	char ch;
	uint32_t key;
	DATA data1;
	intialize();
	do
	{
		ch = getchar();
		switch(ch)
		{
			case 'l':
				scanf(" %u",&key);
				if (_contains(&key))
					printf("\n present");
				else
					printf("\n not there %u",key);
				break;
			case 'i':
				scanf("%u %u",&key,&(data1.data));
				if (_add(&key,&data1))
					printf("\n added");
				else
					printf("\n not added");
				//test();
				break;
			case 'd':
				scanf(" %u",&key);
				if (_remove(&key))
					printf("\n removed");
				else
					printf("\n not there %u",key);
				break;
			case 't':
				during = clock();
				printf("\ntime in ms %u",((during - begin)*1000)/CLOCKS_PER_SEC);
				break;
			case 'f':
				printf("\nload-factor %lf",(1024.0*128.0)/((current_max_segment + 1.0)*1024.0));
				break;
		}
	}while(ch != 'q');
	end = clock();
	printf("time in ms %u %u\n",((end - begin)*1000)/CLOCKS_PER_SEC,begin);
	return 0;
}