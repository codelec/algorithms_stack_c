/*
*credits to the following paper for providing a good insight into hopscotch hashing
people.csail.mit.edu/shanir/publications/disc2008_submission_98.pdf
*/
#define HOP_SIZE
#define ADDR_RANGE
#define MAX_SEGMENTS
#include <stdint.h>
#include <stdbool.h>
/*seperate struct for data to allow future feature addons in
the form of DATA*/
typedef struct
{
	uint32_t data;
}DATA;
typedef struct 
{
	uint32_t _hop_info ;
	uint32_t key;
	DATA data; 
}BUCKET;
/*all the buckets in this array are organized in the form of
*2D array so if in case there is need for extra BUCKETS then
*the number of segments can be doubled or simply incremented
*/
BUCKET segments_arr[][ADDR_RANGE];//declared global at present will be taken care of later on , at present testing
/*current_max_segment is to make sure that
*segment should not be incremented
*/
uint32_t current_max_segment;//start from zero
bool contains(uint32_t *check_key)
{
	uint32_t hash = hash_calc(*check_key);
	uint32_t segment = hash & segment_mask ;
	uint32_t start_bucket_id = hash & bucket_mask ;
	uint32_t start_hop_info = segments_arr[segment][start_bucket_id]->_hop_info;
	uint32_t synergy = ADDR_RANGE - start_bucket_id - 1;
	bool flag1 = 0,flag2 = 0;
	if (current_max_segment - 1 == segment)
		flag1 = 1;
	uint32_t mask = 1, count = 0;
	for (;count =< (HOP_SIZE - 1); count++ , mask <<= 1)
	{
		if ((mask & start_hop_info) && (segments_arr[segment][start_bucket_id + count].key == (*check_key)))
			return true;
		if (flag1 && ((count + start_bucket_id + 1) == ADDR_RANGE))
			break;//since the next row is not yet allocated neither initialized
		if (!flag1 && !flag2 && count => synergy)
		{
			flag2 = 1;
			segment++;
		}
	}
	return false;
}
void find_near_free_distance(uint32_t *free_distance,BUCKET **free_bucket)
{
	
}
bool add(uint32_t *key,DATA *data)
{
	/*if (contains(key))
		return true;
	*/
	uint32_t hash = hash_calc(*key);
	uint32_t segment = hash & segment_mask ;
	uint32_t start_bucket_id = hash & bucket_mask ;
	BUCKET *start_bucket = &segments_arr[segment][start_bucket_id];
	BUCKET *free_bucket;
	uint32_t start_hop_info = start_bucket->_hop_info;
	/*when free_distance crosses synergy it means
	that it has to now move to the next row in the
	segments_arr since it has crossed the ADDR_RANGE 
	of the current row*/
	uint32_t synergy = ADDR_RANGE - start_bucket_id - 1;
	start_again:
	/*
	*flag1 - to prevent checking for free bucket go to the next unallocated row
	*flag2 - to flag the movement from the end reached current row to the next row
	to check for a free bucket
	*flag3 - to signal a resize 
	*/
	bool flag1 = 0 , flag2 = 0 , flag3 = 1;
	if (current_max_segment - 1 == segment)
		flag1 = 1;
	uint32_t mask = 1;
	uint32_t free_distance = start_bucket_id;//start_bucket_id will be subtracted later on
	for (;free_distance =< ADDR_RANGE - 1 + start_bucket_id;++free_distance,mask <<= 1)
	{
		if (!(mask & start_hop_info) && (segments_arr[segment][((flag2)?(free_distance - synergy + 1):free_distance)].key == NULL)){
			free_bucket = &[segment][((flag)?(free_distance - synergy + 1):free_distance)];
			flag3 = 0;
			break;
		}
		if (!flag1 && free_distance => synergy){
			flag2 = 1;
			segment++;
		}
	}
	if (flag3){
		resize();//no free_distance found hence needs to be resized
		goto start_again;
	}
	free_distance -= start_bucket_id;
	if (free_distance < HOP_SIZE){
		free_bucket->key = *key;
		free_bucket->data = *data;
		mask = (1 << free_distance);
		(start_bucket_id->_hop_info) &= mask ; 
	}
	else{
		do{
			find_near_free_distance(&free_distance,&free_bucket);
		}while(free_distance => HOP_SIZE);
		free_bucket->key = *key;
		free_bucket->data = *data;
		mask = (1 << free_distance);
		(start_bucket_id->_hop_info) &= mask ;
	}
}