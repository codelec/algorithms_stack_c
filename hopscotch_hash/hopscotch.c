/*
*credits to the following paper for providing a good insight into hopscotch hashing
*people.csail.mit.edu/shanir/publications/disc2008_submission_98.pdf
*/
/*
*add's the element to a bucket whose location is less that HOP_SIZE
*from the hashed bucket it uses
*find_near_free_location() to move a free bucket in the range of the HOP_SIZE away 
*from the hashed bucket
*/
bool _add(uint32_t *key,DATA *data)
{
	uint32_t hash = hashlittle(key,sizeof(*key),hash_init_val) , segment , start_bucket_id , synergy , mask;
	uint32_t *start_hop_info;
	BUCKET *start_bucket , *free_bucket;
	bool flag1 , flag2 , flag3;
	start_again : //label
	flag1 = 0 , flag2 = 0 , flag3 = 1;//initial declarations
	mask = 1;
	start_bucket_id = hash & bucket_mask ;
	/*when free_distance crosses synergy it means
	that it has to now move to the next row in the
	segments_arr since it has crossed the ADDR_RANGE 
	of the current row provided that the next row has already 
	been allocated*/
	synergy = ADDR_RANGE - start_bucket_id - 1;
	segment = (hash & segment_mask)>>BUCKET_MASK_BITS ;
	start_bucket = &segments_arr[segment][start_bucket_id];
	start_hop_info = &(start_bucket->_hop_info);
	/*
	*flag1 - to prevent checking for free bucket go to the next unallocated row
	*flag2 - to flag the movement from the end reached current row to the next row
	to check for a free bucket
	*flag3 - to signal a resize 
	*/
	if (current_max_segment == segment)
		flag1 = 1;
	/*
	*free_distance is calculated wrt the start_bucket_id
	*following lines 
	*/
	uint32_t free_distance = 0,i;
	for (;free_distance < HOP_SIZE ;++free_distance,mask <<= 1)
	{
		if ((!(mask & (*start_hop_info))) && 
			(segments_arr[segment][(flag2?(free_distance - synergy - 1)
				:(free_distance + start_bucket_id))].key == -1))
		{
			free_bucket = &segments_arr[segment][((flag2)?(free_distance - synergy - 1)
				:(free_distance + start_bucket_id))];
			flag3 = 0;
			break;
		}
		//the following is to initialize the movement 
		//from current row to the next row provided it is allocated 
		if ((!flag1) && (!flag2) && (free_distance == synergy)){
			flag2 = 1;
			segment++;
			continue;
		}
		/*the following condition is to avoid unnecessary loop iterations
		*since the next row is unallocated and it has reached the end of the current row
		*
		*/
		if (flag1 && (free_distance == synergy))
			goto skip_next_for;
	}
	/*this for is seperated since mask cannot exceed HOP_SIZE
	*which results in one less thing to compute in for and one 
	*less condition to evaluate */
	for (i = free_distance; flag3 && i < ADDR_RANGE; ++i)
	{
		if (segments_arr[segment][((flag2)?(i - synergy - 1):(i + start_bucket_id))].key == -1)
		{
			free_bucket = &segments_arr[segment][((flag2)?(i - synergy - 1):(i + start_bucket_id))];
			flag3 = 0;//to indicate no need for resize
			free_distance = i;
			break;
		}
		/*flag2 is used to make sure that segment does not get
		*incremented twice 
		*/
		if ((!flag1) && (!flag2) && (i == synergy)){
			flag2 = 1;
			segment++;
		}
	}
	skip_next_for://label
	if (flag3){
		resize();//no free_location found hence needs to be resized
		goto start_again;
	}
	if (free_distance < HOP_SIZE){
		free_bucket->key = *key;
		free_bucket->data = *data;
		mask = (1 << free_distance);
		(*start_hop_info) |= mask; 
	}
	else{
		if(flag2)
			segment--;// too make sure that it starts from its original row
		uint32_t free_location = start_bucket_id + free_distance ; 
		if (!find_near_free_location(flag1,segment,start_bucket_id,
			&free_location,&free_bucket))
		{
			test();
			resize();
			test();
			goto start_again;
		}
		free_bucket->key = *key;
		free_bucket->data = *data;
		mask = (1 << (free_location - start_bucket_id));
		(*start_hop_info) |= mask ;
	}
}
bool find_near_free_location(bool flag1,
	uint32_t segment,uint32_t start_bucket_id,
	uint32_t *free_location,BUCKET **free_bucket)
{
	/*
	*temp to make sure that if in case the *free_location has not changed
	*means there is no element available to swap the free position with
	*/
	uint32_t i,j,mask,current_bucket_hop_info,temp;
	BUCKET *current_bucket , *potential_free;
	do{
		/*to stop iterating if no change in the *free_location
		 signifying no more free location can be made available*/
		temp = (*free_location);
		for (i = *free_location - (HOP_SIZE - 1); i < *free_location; ++i)
		{
			if (flag1 && (i == (ADDR_RANGE - 1)))
				return 0;
			current_bucket = &segments_arr[((i >= ADDR_RANGE)?(segment + 1):segment)][((i >= ADDR_RANGE)?(i - ADDR_RANGE):i)];
			current_bucket_hop_info = current_bucket->_hop_info;
			mask = 1;
			for (j = i; j < *free_location; ++j,mask <<= 1)
			{
				potential_free = &segments_arr[((j >= ADDR_RANGE)?(segment + 1):segment)][((j >= ADDR_RANGE)?(j - ADDR_RANGE):j)];
				if ((mask & current_bucket_hop_info) && (potential_free->key != -1))
				{
					(*free_bucket)->data = potential_free->data;
					(*free_bucket)->key = potential_free->key;
					potential_free->data.data = -1;
					potential_free->key = -1;
					current_bucket->_hop_info &= (~mask);
					mask <<= (*free_location - j);
					current_bucket->_hop_info |= mask;
					(*free_bucket) = potential_free;
					(*free_location) = j;
				}
			}
		}
	}while(((*free_location - start_bucket_id) >= HOP_SIZE)&&(*free_location != temp));
	if (*free_location != temp)
		return 1;
	else
		return 0;
}
/*
*/
bool _contains(uint32_t *check_key)
{
	uint32_t hash = hashlittle(check_key,sizeof(*check_key),hash_init_val);
	uint32_t segment = ((hash & segment_mask)>>BUCKET_MASK_BITS) ;
	uint32_t start_bucket_id = hash & bucket_mask ;
	uint32_t *start_hop_info = &segments_arr[segment][start_bucket_id]._hop_info;
	uint32_t synergy = ADDR_RANGE - start_bucket_id - 1;
	bool flag1 = 0,flag2 = 0;
	if (current_max_segment == segment)
		flag1 = 1;
	uint32_t mask = 1, count = 0;
	for (;count <= (HOP_SIZE - 1); count++ , mask <<= 1)
	{
		if ((mask & (*start_hop_info)) && (segments_arr[(flag2)?(segment + 1):segment][start_bucket_id + count].key == (*check_key)))
			return true;
		if (flag1 && ((count + start_bucket_id + 1) == ADDR_RANGE))
			break;//since the next row is not yet allocated neither initialized
		if (!flag1 && !flag2 && count >= synergy)
		{
			flag2 = 1;
			segment++;
		}
	}
	return false;
}
/*
*/
bool _remove(uint32_t *key)
{
	uint32_t hash = hashlittle(key,sizeof(*key),hash_init_val);
	uint32_t segment = ((hash & segment_mask)>>BUCKET_MASK_BITS) ;
	uint32_t start_bucket_id = hash & bucket_mask ;
	BUCKET *found_bucket;
	uint32_t i = 0,mask = 1;
	bool flag1 = 0,flag2 = 0;//to allow segment to increment only once
	uint32_t *start_hop_info = &(segments_arr[segment][start_bucket_id]._hop_info);
	for (;i < HOP_SIZE; ++i,mask <<= 1)
	{
		if ((mask & (*start_hop_info)) && 
			(segments_arr[segment][((start_bucket_id + i) >= ADDR_RANGE) ?
			 (start_bucket_id + i - ADDR_RANGE) : (start_bucket_id + i)].key == *key))
		{
			found_bucket = &segments_arr[segment][((start_bucket_id + i) >= ADDR_RANGE) ?
			 ((start_bucket_id + i) - ADDR_RANGE) : (start_bucket_id + i)];
			found_bucket -> key = -1;
			found_bucket -> data.data = -1;
			(*start_hop_info) &= (~mask);//clear the element also from the _hop_info
			return true;	
		}
		if (flag1 && ((i + start_bucket_id + 1) == ADDR_RANGE))
			break;//since the next row is not yet allocated neither initialized
		if (!flag1 && !flag2 && ((i + start_bucket_id + 1) == ADDR_RANGE))
		{
			flag2 = 1;
			segment++;
		}
	}
	return false;
}
/*
*/
void resize()
{
	uint32_t i,j,key,segment;
	DATA temp;
	for (i = current_max_segment + 1; i < 2*(current_max_segment + 1); ++i)	{
		for (j = 0; j < ADDR_RANGE; ++j)
		{
			segments_arr[i][j].key = -1;
			segments_arr[i][j].data.data = -1;
			segments_arr[i][j]._hop_info = 0;
		}
	}
	current_max_segment = 2*current_max_segment + 1;
	if ((current_max_segment-1)!= 0)
		segment_mask = (segment_mask << 1) + bucket_mask + 1;//example 100 -> 1100 -> 11100 -> 111100 
	else
		segment_mask = 1<<BUCKET_MASK_BITS;
	uint32_t allocated_bucket_id , hash ;
	for (i = 0; i <= current_max_segment; ++i)
	{
		for (j = 0;j < ADDR_RANGE; ++j)
		{
			/*in the following lines a key in bucket will only be reallocated iff the new 
			*segment_mask gives it another segment(row) than those that were previously available
			*/
			if (segments_arr[i][j].key != -1){
				hash = hashlittle(&segments_arr[i][j].key,sizeof(segments_arr[i][j].key),hash_init_val);
				if(((hash & segment_mask)>>BUCKET_MASK_BITS) != i){
					key = segments_arr[i][j].key;
					temp = segments_arr[i][j].data;
					segments_arr[i][j].key = -1;
					segments_arr[i][j].data.data = -1;
					allocated_bucket_id = hash & bucket_mask ;
					segment = hash & segment_mask;
					if (allocated_bucket_id <= j)
						(segments_arr[i][allocated_bucket_id]._hop_info) &= (~(1<<(j - allocated_bucket_id)));
					else
						(segments_arr[i - 1][allocated_bucket_id]._hop_info) &= (~(1<<(ADDR_RANGE - allocated_bucket_id + j)));	
					_add(&key,&temp);
				}
			}
		}
	}
}