#include <stdlib.h>
#include <stdio.h>
#include "lookup.c"
#include "hopscotch.h"
int main(int argc, char const *argv[])
{
	char a[]="keyy";
	printf("%u\n",hashlittle(a,sizeof(a)/sizeof(a[0]),1));
	printf("%s\n",a);
	printf("%u\n", ~(0b10) + 1);
	return 0;
}