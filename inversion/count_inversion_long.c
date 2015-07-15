#include<stdio.h>
void fill_array(long* sort,long n);
long count_and_merge_sort(long* sort,long n);
long merge_and_count_split_inv(long* one_half,long* two_half,long n);
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
long count_and_merge_sort(long* sort,long n)
{
	if (n==1)
		return 0;
	else
	{
		long* one_half= sort;
		long* two_half = sort + n/2;
		long x,y,z;
		x=count_and_merge_sort(one_half,n/2);
		y=count_and_merge_sort(two_half,(n%2==0?n/2:n/2+1));
		z=merge_and_count_split_inv(one_half,two_half,n);
		return x+y+z;
	}
}
long merge_and_count_split_inv(long* one_half,long* two_half,long n)
{
	long i=0,j=0,a=n/2,k=0,count=0,b=(n%2==0?n/2:n/2+1),temp[n];
	while(i<a && j<b)
	{
		if (one_half[i]<two_half[j]){
			temp[k]=one_half[i];
			i++,k++;
		}
		else
		{
			temp[k]=two_half[j];
			count+=(a-i);
			j++,k++;
		}
	}
	if (i<a)
	{
		while(i<a&&k<n)
		{
			temp[k]=one_half[i];
			i++,k++;
		}
	}
	else
	{
		while(j<b&&k<n)
		{
			temp[k]=two_half[j];
			j++,k++;
		}
	}
	for(i=0;i<n;i++)
	{
		if(i<a)
			one_half[i]=temp[i];
		else
			two_half[i-a]=temp[i];
	}
	return count;
}
