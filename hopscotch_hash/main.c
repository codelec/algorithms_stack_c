#define HOP_SIZE
#define ADDR_RANGE
#define MAX_SEGMENTS
#include <stdint.h>
#include <stdbool.h>
typedef struct
{
	uint32_t key;
}KEY;
typedef struct
{
	uint32_t data;
}DATA;
typedef struct 
{
	uint32_t _hop_info ;
	KEY	*key;
	DATA *data; 
}BUCKET;
BUCKET segments_arr[][ADDR_RANGE];
bool contains(KEY *check_key)
{
	uint32_t hash = hash_calc(check_key->key);
	uint32_t segment = hash & segment_mask ;
	uint32_t bucket_id = hash & bucket_mask ;
	BUCKET *start_bucket = segments_arr[segment][bucket_id];
	uint32_t start_hop_info = start_bucket->_hop_info;
	uint32_t mask = 1, count = 0;
	for (;count =< (HOP_SIZE - 1); count++ , mask <<= 1)
	{
		if ((mask & start_hop_info) && (segments_arr[segment][bucket_id + count]->key->key == check_key->key))
		{
			return true;
		}
	}
	return false;
}
bool add(KEY *key,DATA *data)
{
	/*if (contains(key))
	{
		return true;
	}*/
	uint32_t hash = hash_calc(check_key->key);
	uint32_t segment = hash & segment_mask ;
	uint32_t bucket_id = hash & bucket_mask ;
	BUCKET *start_bucket = segments_arr[segment][bucket_id];
	uint32_t start_hop_info = start_bucket->_hop_info;
	uint32_t free_distance = 0;
	/*when free_distance crosses synergy it means
	that it has to now move to the next row in the
	segments_arr since it has crossed the ADDR_RANGE 
	of the current row*/
	uint32_t synergy = ADDR_RANGE - bucket_id - 1;
	bool flag = 0;
	for (; free_distance =< ADDR_RANGE - 1; ++free_distance)
	{
		if (segments_arr[segment][((flag)?(free_distance - synergy + 1):free_distance)]->key == NULL)
			break;
		if (!flag && free_distance => synergy)
		{
			flag = 1;
			segment++;
		}
	}
	if (flag == 1)
		segment -- ;
	if (free_distance =< (HOP_SIZE - 1))
	{
		
	}
}