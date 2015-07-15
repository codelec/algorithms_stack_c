to run the demo 
>gcc main.c

in order to use the merge sort algorithm use just need to type the following line in the start of your program 
>\#include \"logic_merge_sort.c\"

copy the file logic_merge_sort.c (no need to add main.c) to the root of your program folder 

the API to use merge sort is:
>merge_sort(array_name,array_length)

the array should be consisting only of integers 
incase it is to be used for floating point numbers then some modifications have to be made in the file 
logic_merge_sort.c
1)every array used in the file should be of float type 
2)the for loop variables should remain of int type