#include <math.h>
#include <stdio.h>
int multiply(int num1,int num2);
int
main(void)
{
int num1,num2,mult;
printf(" enter the number whose product is to be calculated : ");
scanf(" %d",&num1);
printf(" %d ",num1);
scanf(" %d",&num2);
printf(" %d ",num2);
mult=multiply(num1,num2);
printf(" %d\n",mult);
return (0);
}
int
multiply(int num1,int num2)
{
if (((num1/10)==0)&&((num2/10)==0))
{
	printf(" %d %d\n",num1,num2 );
	return num1*num2;
}
else
{
	int num1_one,num1_two,num2_one,num2_two,pro13,pro24,pro1p3_2p4,n=0,maxim=((num1>num2)?num1:num2);
	while (maxim>0)
	{
		maxim/=10;
		n++;
	}
	num1_one = num1 / (int)(pow((double)10,(double)(n/2)));
	num1_two = num1 % (int)(pow((double)10,(double)n/2));
	num2_one = num2 / (int)(pow((double)10,(double)n/2));
	num2_two = num2 % (int)(pow((double)10,(double)n/2));
	printf(" %d %d %d %d\n",num1_one,num1_two,num2_one,num2_two );
	pro13=multiply(num1_one , num2_one);
	pro24=multiply(num1_two , num2_two);
	pro1p3_2p4=multiply((num1_one + num1_two),(num2_two + num2_one)) - pro13 - pro24;
	return pow(10,n) * pro13 + pow(10,n/2) * pro1p3_2p4 + pro24;
}
}
