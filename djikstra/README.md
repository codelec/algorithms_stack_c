#INTRODUCTION
to use the demo 
>gcc main.c

the input to the program can be changed modifying the file test12 and the input should be modified in the following manner
><*node*> <*node connected to*> <*weight of the edge connecting them*> 

It is assumed that the weight of each edge is an integer

accordingly do change the 
>```#define NUM_NODES 4```  -> main.c
 
inorder to use logic_djikstra.c
you need to add the following lines in your main program 
>```#include "logic_djikstra.c"```

you can call the dkjikstra function in the following manner
>```djikstra(source_node,array in which shortpaths to all the nodes is to be stored)```
