void bfs(vertex* s)
{
	list *head=(list*)malloc(sizeof(list));//head of the queue
	list *tail,*traverse,*temp;
	s -> explored = 1;
	s -> level = 1;
	head -> node = s;
	tail = head;//assiging it to tail only after memory space is alloted
	do
	{	
		traverse = head -> node -> connected_to;//taverse points to the list consisting of the nodes connected a particular node at present first in the list
		while( traverse != NULL)//traverse the connected_to
		{
			if ((traverse -> node -> explored) != 1)
			{
				traverse -> node -> explored = 1;//marking the node just added to the queue as exlpored
				traverse -> node -> level = head -> node -> level + 1;//level child = level parent + 1
				tail -> next_connection = (list*)malloc(sizeof(list));
				tail = tail -> next_connection;//tail being set for the next addition to the queue
				tail -> node = traverse -> node;//adding the traverse node to the queue since being explored for the first time
				tail -> next_connection = NULL;
			}
			traverse = traverse -> next_connection;
		}
		temp = head;
		head = head -> next_connection;//head now points to the next node in the queue
		free(temp);
	}while(head != NULL);
}