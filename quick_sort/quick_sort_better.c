#include<stdio.h>
void fill_array(int* fill_arr,int n);
void output_array(int* output_arr,int n);
void quick_sort(int* to_sort,int n);
int select_partition(int* to_sort,int n);
int count=0;
int
main(void)
{
int n;
scanf(" %d",&n);
int input_arr[n];
fill_array(input_arr,n);
quick_sort(input_arr,n);
output_array(input_arr,n);
printf(" %d\n",count);
return (0);
}
void fill_array(int* fill_arr,int n)
{
int i;
for (i=0;i<n;i++)
	scanf(" %d",&fill_arr[i]);
}
void output_array(int* output_arr,int n)
{
int i;
for (i=0;i<n;i++)
	printf("%d",output_arr[i]);
printf("\n");
}
void quick_sort(int* to_sort,int n)
{
if(n==1)
{return ;}
else
{
int temp,i=0,j,p=select_partition(to_sort,n);
if(p!=0)
{
	temp=to_sort[p];
	to_sort[p]=to_sort[0];
	to_sort[0]=temp;
}
for (j=i+1;j<n;j++){
if(to_sort[j]<to_sort[0])
{
	temp=to_sort[j];
	to_sort[j]=to_sort[i+1];
	to_sort[i+1]=temp;
	i++;
}
}
	temp=to_sort[0];
	to_sort[0]=to_sort[i];
	to_sort[i]=temp;
count+=(n-1);
if(i>1)
{
quick_sort(to_sort,i);}
if(n-(i+1)>1)
{
quick_sort(to_sort+(i+1),n-(i+1));}
}
}
int
select_partition(int* to_sort,int n)
{
int mid=(n%2==0)?(n/2-1):(n/2);
if((to_sort[0] < to_sort[mid] && to_sort[mid] < to_sort[n-1])||(to_sort[0] > to_sort[mid] && to_sort[mid] > to_sort[n-1]))
{return (mid);}
else if((to_sort[0] < to_sort[n-1] && to_sort[mid] > to_sort[n-1])||(to_sort[0] > to_sort[n-1] && to_sort[mid] < to_sort[n-1]))
{return (n-1);}
else
{return (0);}
}
