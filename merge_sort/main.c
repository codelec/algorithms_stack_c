#include<stdio.h>
#include "logic_merge_sort.c"
void fill_array(int *sort, int n)
{
	int i;
	printf("enter the elements of array seperated by a space : ");
	for(i = 0;i < n;i ++)
		scanf(" %d",&sort[i]);
}
void output_sort(int *sorted, int n)
{
	int i;
	for(i = 0;i < n;i ++)
		printf(" %d",sorted[i]);
	printf("\n");
}
int main(void)
{
	int n;
	printf("enter the array size that is to be sorted :");
	scanf(" %d", &n);
	int sort[n];
	fill_array(sort, n);
	output_sort(sort , n);
	merge_sort(sort , n);
	output_sort(sort, n);
	return (0);
}