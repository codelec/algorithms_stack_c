//void print_nodes_in_list(list *head);
void remove_node(list1 **head,vertex *toremove)
{
	list1 *traverse,*prev_traverse;
	while(((*head) != NULL) && ((*head)->node->id == toremove->id))
	{
		traverse = (*head);
		(*head) = (*head)->next_connection;
		free(traverse);
	}
	if (((*head) == NULL) || ((*head)->next_connection == NULL))
		{return ;}
	prev_traverse = (*head);//stores the addr of the contents being pointed by the current head which is now not the node of interest 
	//prev_traverse is used to store the addr of the parent node(in terms of list)
	traverse = (*head)->next_connection;//points to next node in list
	while(traverse != NULL)//to loop through the rest of the contents of the list to check whether it contains the node of interest or not
	{
		if(((traverse->node)->id) == (toremove->id))
		{
			((prev_traverse)->next_connection) = (traverse->next_connection);
			free(traverse);
			traverse = ((prev_traverse)->next_connection);
			continue;//continues to the next iteration to prevent another unnecessary hop
		}
		traverse = (traverse->next_connection);//hop
	}	
}
vertex *find_min_weight_node(list1 *head,int *shortpath,int *num_nodes_explored)
{
	int min_weight = max_weight;//initializing it with maximum possbile weight stored in the macro
	list1 *traverse = head;
	vertex *min_weight_node;
	while(traverse != NULL)//traverse the connected_to
	{
		if ((((traverse->parent)->explored) != ((traverse->node)->explored)) && (((traverse->weight) + shortpath[((traverse->parent)->id) - 1]) < min_weight))
		{
			min_weight = (traverse->weight) + shortpath[((traverse->parent)->id) - 1];
			min_weight_node = (traverse->node);
		}
		traverse = traverse->next_connection;
	}
	shortpath[(min_weight_node->id) - 1] = min_weight;
	(min_weight_node->explored) = 1;
	(*num_nodes_explored)++;
	return min_weight_node;
}
void dijkstra(vertex* s,int *shortpath)
{
	list1 *head,*tail;//head of the queue
	list *traverse;
	int num_nodes_explored = 0,flag = 0;
	vertex *min_weight_node = s;
	s->explored = 1;//to mark start as explored
	num_nodes_explored++;//since one node is now explored
	shortpath[(s->id) - 1] = 0;
	while(num_nodes_explored < num_nodes)
	{	
		traverse = min_weight_node->connected_to;//taverse the list consisting of the nodes connected a particular node at present first in the list
		while((traverse != NULL) && (((traverse->node)->explored) != 1))//traverse the connected_to
		{
	printf(" in dijkstra\n");
			if (flag == 0)
			{
				tail = (list1*)malloc(sizeof(list1));
				head = tail;
				flag = 1;
			}
			else
			{
				tail->next_connection = (list1*)malloc(sizeof(list1));
				tail = tail->next_connection;
			}
			tail->parent = min_weight_node;
			tail->node = traverse->node;//adding the traverse node to the queue
			tail->weight = traverse->weight;
			tail->next_connection = NULL;//tail=(tail->next_connection);//tail being set for the next addition to the queue
			traverse = traverse->next_connection;
		}
		//print_nodes_in_list(head);
		min_weight_node = find_min_weight_node(head,shortpath,&num_nodes_explored);
		remove_node(&head,min_weight_node);
	}
}