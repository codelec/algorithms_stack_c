void merge(int *,int *,int *);
void merge_sort(int *, int );
void divide_in_two(int *,int *,int *);
void output_sort(int *, int );
void merge_sort(int *list, int n)
{
	if(n == 1)
	{	return ;}
	else
	{
		int first_half[(n / 2)],second_half[(n % 2 != 0 ? (n / 2) + 1 : (n / 2))];
		printf("%d %d\n",(n / 2),(n % 2 != 0 ? (n / 2) + 1 : (n / 2)) );
		divide_in_two(list,first_half,second_half);
		merge_sort(first_half,sizeof(first_half) / sizeof(first_half[0]));
		merge_sort(second_half,sizeof(second_half) / sizeof(second_half[0]));
		merge(list,first_half,second_half);
	}
}
/*
*divide_in_two
*is passed by refrence the two arrays that were created in the function merge_sort
*
*/
void divide_in_two(int *list,int *first_half,int *second_half)
{
	int i,n = sizeof(list) / sizeof(list[0]) ;
	for(i = 0; i < n; i ++)
	{
		if (i < (n / 2))
		{
			first_half[i] = list[i];
		}
		else
		{
			second_half[i - (n / 2)] = list[i];
		}
	}
	output_sort(first_half,(n / 2));
	output_sort(second_half,sizeof(second_half) / sizeof(second_half[0]));
}
void merge(int *list,int *first_half,int *second_half)
{
	int k = 0,a = sizeof(first_half) / sizeof(first_half[0]) , b = sizeof(second_half) / sizeof(second_half[0]) , i = 0 , j = 0 ;
	while(i < a && j < b)
	{
		if (first_half[i] < second_half[j])
		{	
			list[k] = first_half[i];
			i++,k++;
		}
		else
		{	
			list[k]=second_half[j];
			j++,k++;
		}
	}
	if (i == a)
	{
		list[k]=second_half[j];
	}
	else if (j == b)
	{
		list[k] = first_half[i];
	}
	else
	{}
	output_sort(list,a + b);
}