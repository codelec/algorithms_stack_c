void merge(int *,int ,int *,int *);
void divide_in_two(int *,int ,int *,int *);
void merge_sort(int *list, int n)
{
	if(n == 1)
	{	return ;}
	else
	{
		int first_half[(n / 2)],second_half[(n % 2 != 0 ? (n / 2) + 1 : (n / 2))];
		divide_in_two(list,n,first_half,second_half);
		merge_sort(first_half,(n / 2));
		merge_sort(second_half,(n % 2 != 0 ? (n / 2) + 1 : (n / 2)));
		merge(list,n,first_half,second_half);
	}
}
void divide_in_two(int *list,int list_size,int *first_half,int *second_half)
{
	int i ;
	for(i = 0; i < list_size; i ++)
	{
		if (i < (list_size / 2))
		{
			first_half[i] = list[i];
		}
		else
		{
			second_half[i - (list_size / 2)] = list[i];
		}
	}
}
/*
*compare the first element of each half's and accordingly the lower one of the two should
*be put in the "list" and this should be done untill all the elements end up in list
*/
void merge(int *list,int list_size,int *first_half,int *second_half)
{
	int k = 0,a = list_size / 2 , b = (list_size % 2 != 0 ? (list_size / 2) + 1 : (list_size / 2)) , i = 0 , j = 0 ;
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
}