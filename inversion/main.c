#include <stdio.h>
#include "logic_count_inversion.c"
void fill_array(long* sort,long n);
int
main(void)
{
	long n;
	printf(" enter the number of elements to be entered : ");
	scanf("%ld",&n);
	long sort[n];
	fill_array(sort, n);
	printf(" the number of inversions : %ld\n",count_and_merge_sort(sort,n));
	return (0);
}
void
fill_array(long* sort,long n)
{
	long i;
	for(i=0;i<n;i++)
		scanf("%ld",(sort+i));
}