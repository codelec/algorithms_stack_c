int count=0;//to keep a track of the number of connected components during dfs loop
vertex *s;//keeps a record of the node from where the last dfs call was from
int t=0;//increments after a node is completely done with in a particular dfs loop call
int order_id[num_nodes];//stores the id of the nodes in the required order
void dfs(vertex*,int);//int call_type = 1 for the second call = 2 for the first call
void dfs_loop(int);//int call_type = 1 for the second call = 2 for the first call
void isitintop4(int n);
#include "logic_scc.c"