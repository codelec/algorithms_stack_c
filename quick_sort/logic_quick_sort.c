int select_partition(int *,int n);
void quick_sort(int *,int n);
int select_partition(int *,int n)
{
	int mid = (n % 2 == 0) ? (n / 2 - 1) : (n / 2);
	if((to_sort[0] < to_sort[mid] && to_sort[mid] < to_sort[n - 1]) || (to_sort[0] > to_sort[mid] && to_sort[mid] > to_sort[n - 1]))
	{return (mid);}
	else if((to_sort[0] < to_sort[n - 1] && to_sort[mid] > to_sort[n - 1]) || (to_sort[0] > to_sort[n - 1] && to_sort[mid] < to_sort[n - 1]))
	{return (n - 1);}
	else
	{return (0);}
}
void quick_sort(int *to_sort,int n)
{
	if(n == 1)
	{return ;}
	else
	{
		int temp,i = 0,j,p = select_partition(to_sort,n);
		if(p != 0)
		{
			temp = to_sort[p];
			to_sort[p] = to_sort[0];
			to_sort[0] = temp;
		}
		for (j = i + 1;j < n;j ++){
			if(to_sort[j] < to_sort[0])
			{
				temp = to_sort[j];
				to_sort[j] = to_sort[i + 1];
				to_sort[i + 1] = temp;
				i++;
			}
		}
		temp = to_sort[0];
		to_sort[0] = to_sort[i];
		to_sort[i] = temp;
		if(i > 1)
		{
			quick_sort(to_sort,i);
		}
		if(n - (i + 1) > 1)
		{
			quick_sort(to_sort + (i + 1),n - (i + 1));
		}
	}
}