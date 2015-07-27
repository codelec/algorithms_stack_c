>Each bucket contains a key , data and hop info

hop info stores the status of the other HOP_SIZE - 1 in the form of bit map
	locations some of them containing keys that were hashed to this
	bucket but were moved to another since the current one was occupied

	
flags are used to ensure smooth movement from the current row to the
next row when in search for a free bucket in the following functions

>bool _add(uint32_t \*key,DATA *data)

add's the element to a bucket whose location is less than HOP_SIZE
from the hashed bucket it uses find_near_free_location() to move a 
free bucket in the range of the HOP_SIZE away from the hashed bucket
in case of unavailability of free bucket in the HOP_SIZE range . 
resize() is invoked if incase find_near_free_function() returns failure
if it is not able to make a free bucket in the HOP_SIZE range . 
returns true for succesful addition 

>void resize()
	
doubles the current number of rows , segment mask is changed
iterates over all the keys in the table and rehashes all those keys 
with different segment after masking with the new segment mask

>bool _contains(uint32_t *key)
	
checks the hop info of the hashed bucket and accordingly then checks 
each bucket

>bool _remove(uint32_t *key)
	
similar to _contains() the only difference being it deletes the key on finding it

>bool find_near_free_location(bool flag1,uint32_t segment,uint32_t start_bucket_id,
	uint32_t \*free_location,BUCKET **free_bucket)
		
flag1 - no need to hash key again to know about the movement to th next to row
segment - row of the hashed bucket 
start_bucket_id - column of the hashed bucket
free_location - pointer so that the new free location can be updated after the function returns
free_bucket - same concept as free_location

Starting at the bucket HOP RANGE−1 slots below the empty bucket, the method
examines each bucket in ascending order until it reaches the empty bucket .
For each bucket, it iterates through its hop info bit map, from lowest index
to highest, looking for an occupied bucket whose key can be moved to the empty
bucket