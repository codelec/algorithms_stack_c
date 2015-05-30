#include<stdio.h>
void swap(char *a,char *b)
{
	char temp ;
	temp = *a;
	*a = *b;
	*b = temp;
}
void generate(int n,char *a)
{
	int i,j;
	if (n == 1)
	{
		printf("%s\n", a);
	}
	else
	{
		for (i = 0; i < n; ++i)
		{
			generate(n-1,a);
			if (n % 2 == 0)
			{
				swap(a + i, a + n - 1);
			}
			else
			{
				swap(a , a + n - 1);	
			}
		}
	}
}
int main(int argc , char *argv[])
{
	generate(atoi(argv[1]),argv[2]);
}