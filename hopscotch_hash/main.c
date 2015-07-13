#include <stdlib.h>
#include <stdio.h>
#include "lookup.c"
#include "hopscotch.h"
int main(int argc, char const *argv[])
{
	printf("%u\n",hashlittle("keyy",sizeof("key"),1));
	return 0;
}