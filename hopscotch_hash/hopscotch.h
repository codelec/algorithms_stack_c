/*
*credits to the following paper for providing a good insight into hopscotch hashing
people.csail.mit.edu/shanir/publications/disc2008_submission_98.pdf
*/
#define HOP_SIZE 4
#define ADDR_RANGE 16
#define BUCKET_MASK_BITS 4
/*changing this should also change bucket_mask initialization in 
this file itself and also in hopscotch.c file in resize() initialization
of segment_mask should be accordingly changed */
//#define MAX_SEGMENTS 16
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
uint32_t current_max_segment = 0;//start from zero .. row0 is the maximum default
uint32_t segment_mask = 0;
/*
*this value can be changed if in case the program on execution
*results in Segmentation default core dumped which has 
*avoided that error
*/
uint32_t hash_init_val = 2; 
uint32_t bucket_mask = 0b01111;
bool _contains(uint32_t *);
void resize();
bool _remove(uint32_t *);
bool _add(uint32_t *,DATA *);
bool find_near_free_location(bool ,uint32_t ,uint32_t ,uint32_t *,BUCKET **);
#include "hopscotch.c"