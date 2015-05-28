void dfs(vertex* s)
{
	s -> explored = 1;
	list *traverse;
	traverse = s -> connected_to;//taverse the list consisting of the nodes connected to s
	while(traverse != NULL)//traverse the connected_to
	{
		if (traverse -> node -> explored != 1)
		{
			traverse -> node -> explored = 1;//marking the node just added to the queue as exlpored
			dfs(traverse -> node);
		}
		traverse = traverse -> next_connection;
	}
}