void print_node_details(node *root)
{
	printf(" %d %d %d\n",root->id,root->size,root->data);
}
/*returns the node which has the same search_id*/
node *search(int search_id , node *root)
{
	if ((root->id > search_id)&&(root->left_child != NULL))
		return search(search_id,root->left_child);
	else if ((root->id < search_id)&&(root->right_child != NULL))
		return search(search_id,root->left_child);
	else
		return root;
}
/*
*increments/decrements the size of parent
*depending on a new insertion or deletion
*val is used to indicate incrment or decrement
*/
void update_size(node *from_child,bool val)
{
	node *parent = from_child->parent;
	while(parent != NULL)
	{
		(parent->size)+= (val?1:(-1));
		parent = parent->parent;
	}
}
/*
*returns false in case the tree is empty 
*since could be that the node was just deleted
*structure change results in change the size of node sub-trees
*hence  updat_size called
*/
bool insert(node *add_me,node *root)
{
	if(root == NULL)
		return false;
	node *root_add = search(add_me->id,root);
	if (root_add->id > add_me->id){
		add_me->parent = root_add;
		root_add->left_child = add_me;
	}
	else{
		add_me->parent = root_add;
		root_add->right_child = add_me;
	}
	add_me->size = 1;
	update_size(add_me,1);
	return true;
}
/*recursively finds the minimum of the sub-tree under the root*/
node *min_node(node *root)
{
	while(root->left_child != NULL)
		root = root->left_child;
	return root;
}
/*recursively finds the maximum of the sub-tree under the root*/
node *max_node(node *root)
{
	while(root->right_child != NULL)
		root = root->right_child;
	return root;
}
/*predecessor - largest node smaller that root*/
node *predecessor(node *root)
{
	if(root->left_child != NULL)
		return max_node(root->left_child);
	else
	{
		node *temp = root->parent;
		while((temp != NULL)&&(temp->id > root->id))
			temp = temp->parent;
		if (temp == NULL)
			return NULL;
		return temp;
	}
}
//
void print_keys_in_order(node *root)
{
	if(root->left_child != NULL)
		print_keys_in_order(root->left_child);
	print_node_details(root);
	if(root->right_child != NULL)
		print_keys_in_order(root->right_child);
}
void select(node *root,int i)
{
	int size_l;
	if (root->left_child != NULL)
		size_l = root->left_child->size;
	else
		size_l = 0;
	if ((size_l + 1) == i)
		return root;
	else if(size_l > i)
		return select(root->left_child,i);
	else
		return select(root->right_child,i - size_l - 1);	
}
bool delete(node *root)
{
	node *child_to_move;
	if((root->left_child != NULL) && (root->right_child != NULL)){
		child_to_move = predecessor(root);
		if(child_to_move->parent == root)
			child_to_move->parent = root->parent;
		else{
			child_to_move->parent->right_child = NULL;
			child_to_move->left_child = root->left_child;
		}
		child_to_move->right_child = root->right_child;
		if(child_to_move->id > root->parent->id)
			root->parent->right_child = child_to_move;
		else
			root->parent->left_child = child_to_move;	
		goto skip;
	}
	else if(root->left_child == NULL && root->right_child == NULL)
		child_to_move = NULL;
	else
		child_to_move = (root->left_child != NULL) ? root->left_child : root->right_child;
	if (root->parent->id > root->id)
		root->parent->left_child = child_to_move;
	else
		root->parent->right_child = child_to_move;		 
	skip:
	update_size(root,)
	free(root);
}