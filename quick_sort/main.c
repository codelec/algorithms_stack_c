#include<stdio.h>
#include "logic_quick_sort.c"
void fill_array(int *fill_arr,int n);
void output_array(int *output_arr,int n);
int main(void)
{
	int n;
	scanf(" %d",&n);
	int input_arr[n];
	fill_array(input_arr,n);
	quick_sort(input_arr,n);
	output_array(input_arr,n);
	return (0);
}
void fill_array(int *fill_arr,int n)
{
	int i;
	for (i = 0;i < n;i++)
		scanf(" %d",&fill_arr[i]);
}
void output_array(int *output_arr,int n)
{
	int i;
	for (i = 0;i < n;i++)
		printf("%d ",output_arr[i]);
	printf("\n");
}