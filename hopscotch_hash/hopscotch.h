/*
*credits to the following paper for providing a good insight into hopscotch hashing
people.csail.mit.edu/shanir/publications/disc2008_submission_98.pdf
*/
#define HOP_SIZE 32
#define ADDR_RANGE 256
/*changing this should also change bucket_mask initialization in 
this file itself and also in hopscotch.c file in resize() initialization
of segment_mask should be accordingly changed */
#define MAX_SEGMENTS 16
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
uint32_t segment_mask = 0;
uint32_t bucket_mask = 0b011111111;
bool _contains(uint32_t *check_key);
void resize();
void _remove(uint32_t *key,DATA *data);
bool _add(uint32_t *key,DATA *data);
bool find_near_free_location(bool flag1,bool flag2,uint32_t segment,uint32_t start_bucket_id,uint32_t *free_location,BUCKET **free_bucket);
bool contains(uint32_t *check_key);
#include "hopscotch.c"