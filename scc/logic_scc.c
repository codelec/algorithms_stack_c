void dfs_loop(int call_type)
{
	int i;
	for (i = num_nodes - 1; i >= 0; i--)
	{
		if (call_type==2)
		{
			if (node[i].explored!=1)
			{
				dfs(&node[i],call_type);
			}
		}
		else if(call_type == 1)
		{
			if (node[order_id[i]-1].explored!=1)
			{
				s=&node[order_id[i]-1];
				(s->explored)=1;
				dfs(&node[order_id[i]-1],call_type);
				isitintop4(count);
				count=0;
			}
		}
	}
}
void dfs(vertex* dfs_s,int call_type)
{
	(dfs_s->explored)=1;
	list* traverse;	
	traverse=dfs_s->connected_to;//taverse the list consisting of the nodes connected a particular node at present first in the list
	if (call_type == 1)
	{
		count++;
		dfs_s->leader_id=s->id;
	}
	while((traverse->node) != (vertex*)NULL)//traverse the connected_to
	{
		if (((traverse->node)->explored)!=1)
		{
			((traverse->node)->explored)=1;//marking the node just added to the queue as exlpored
			dfs(traverse->node,call_type);
		}
		traverse=traverse->next_connection;
	}
	if (call_type == 2)
	{
		order_id[t++]=(dfs_s->id);
	}
}
void isitintop4(int n)
{
	if(n>a1)
	{
		a5=a4,a4=a3,a3=a2,a2=a1,a1=n;
	}
	else if (n>a2)
	{
		a5=a4,a4=a3,a3=a2,a2=n;	
	}
	else if (n>a3)
	{
		a5=a4,a4=a3,a3=n;
	}
	else if (n>a4)
	{
		a5=a4,a4=n;
	}
	else if (n>a5)
	{
		a5=n;
	}
}