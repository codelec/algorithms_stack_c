#include <stdio.h>
#include "pcg_basic.h"
int main()
{
	uint32_t count = 1024*128 - 1;
	uint32_t rounds = 1000000 + 1024*256 - 1;
	pcg32_random_t rng;
	uint32_t arr[1024*128],temp;//arr is used 
	pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&rounds);
	while(count--)
	{
		arr[count] = pcg32_boundedrand_r(&rng, 0b1111111111111111111111111111111);
		printf("i\n");
		printf(" %u %u\n",arr[count],pcg32_boundedrand_r(&rng, 0b1111111111111111111111111111111));
	}
	printf("t\n");
	printf("f\n");
	count = 900000;
	while(--count){
		printf("l\n");
		temp = pcg32_boundedrand_r(&rng, 1024*128 - 1);
		printf(" %u\n",arr[temp]);
	}
	printf("t\n");
	count = 100000;
	while(--count){
		printf("d\n");
		printf(" %u\n",arr[pcg32_boundedrand_r(&rng, 1024*128 - 1)]);	
	}
	printf("t\nq");
}