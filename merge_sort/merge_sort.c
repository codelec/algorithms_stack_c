#include<stdio.h>
#include "declarations.h"
#include "logic_merge_sort.c"
int main(void)
{
	int n;
	printf("enter the array size that is to be sorted :");
	scanf(" %d", &n);
	int sort[n];
	fill_array(sort, n);
	printf(" %d",sort[0]);
	output_sort(sort , n);
	merge_sort(sort , n);
	output_sort(sort, n);
	return (0);
}
void fill_array(int *sort, int n)
{
	int i;
	printf("enter the elements of array seperated by a space : ");
	for(i = 0;i < n;i ++)
	{
		scanf(" %d",&sort[i]);
		printf(" %d",sort[i]);
	}
}
void output_sort(int sort[], int n)
{
	int i;
	for(i = 0;i < n;i ++)
		printf(" %d",sort[i]);
}
/*void merge_sort(int *list, int n)
{
	int length_one = n / 2,one_half[length_one],second_half[n % 2 != 0 ? length_one + 1 : length_one];
	if(n == 1)
	{	return ;}
	else
	{
		divide_in_two(list,one_half,second_half);
		merge_sort(one_half,sizeof(one_half) / sizeof(one_half[0]));
		merge_sort(second_half,sizeof(second_half) / sizeof(second_half[0]));
		merge(list,one_half,second_half);
	}
}*/
/*
*divide_in_two
*is passed by refrence the two arrays that were created in the function merge_sort
*
*/
/*void divide_in_two(int *list,int *one_half,int *second_half)
{
	int i,n = sizeof(list) * sizeof(list[0]) ;
	for(i = 0; i < n; i ++)
	{
		if (i < (n / 2))
		{
			one_half[i] = list[i];
		}
		else
		{
			second_half[i] = list[i];
		}
	}
}
void merge(int *list,int *one_half,int *second_half)
{
	int k = 0,a = sizeof(one_half) / sizeof(one_half[0]) , b = sizeof(second_half) / sizeof(second_half[0]) , i = 0 , j=0 ;
	while(i < a || j < b)
	{
		if (one_half[i] < second_half[j])
		{	list[k] = one_half[i];
			i ++,k ++;
		}
		else
		{	list[k]=second_half[j];
			j++,k++;
		}
	}
}*/
