#ifndef NXS_DYNAMIC_ARRAY_H
#define NXS_DYNAMIC_ARRAY_H
#include "std.h"

/** NXS_DynamicArray
 * is a dynamic array implementation
 */
typedef struct NXS_DynamicArray_T NXS_DynamicArray;

/** NXS_CreateDynamicArray
 * allocates and initializes a dynamic array
 * \returns the new `NXS_DynamicArray` dynamic array or `NULL` on failure
 * \param typesize the size each member should have, for indexing
 * \param init_cap the initial capacity of the array, can change during its lifespan
 */
NXS_DynamicArray* NXS_CreateDynamicArray(size_t typesize, size_t init_cap);

/** NXS_DestroyDynamicArray
 * clears and frees a dynamic array
 * \param dynarr the dynamic array to destroy
 */
void NXS_DestroyDynamicArray(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayPush
 * adds an item to the end of a dynamic array
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to append to
 * \param data a void pointer to the data to append, make sure the data it points to has the same size as you submitted in `NXS_CreateDynamicArray`
 * \note the data will be copied, not stored through a pointer
 */
bool NXS_DynamicArrayPush(NXS_DynamicArray* dynarr, void* data);

/** NXS_DynamicArrayPop
 * removes last item in array
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to pop from
 */
bool NXS_DynamicArrayPop(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayInsert
 * adds a item at a given index, moving all later items one space up
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to insert in
 * \param index the index to insert at
 * \param data a void pointer to the data to insert, make sure the data it points to has the same size as you submitted in `NXS_CreateDynamicArray`
 */
bool NXS_DynamicArrayInsert(NXS_DynamicArray* dynarr, size_t index, void* data);

/** NXS_DynamicArrayRemove
 * removes an item at a given index, moving all later ones one space down
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to remove from
 * \param index the index of the item to remove
 */
bool NXS_DynamicArrayRemove(NXS_DynamicArray* dynarr, size_t index);

/** NXS_DynamicArrayIndex
 * return the item at a given index
 * \returns a pointer to the data stored at that index or `NULL` on failure
 * \param dynarr the array to index
 * \param index the index to use
 */
void* NXS_DynamicArrayIndex(NXS_DynamicArray* dynarr, size_t index);

/** NXS_DynamicArrayFind
 * searches for a item that matches the provided data and returns the index
 * \returns the index of the item that matches or `NULL` on failure
 * \param dynarr the array to search
 * \param data the data to search for
 */
size_t NXS_DynamicArrayFind(NXS_DynamicArray* dynarr, void* data);

/** NXS_DynamicArraySize
 * returns the capacity of a given dynamic array
 * \returns the capacity, or `(size_t)-1` (-1 cast to unsigned) on failure
 * \param dynarr the array to get the capacity of
 */
size_t NXS_DynamicArraySize(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayCount
 * returns the amount of items in the array (the logical size)
 * \returns the number of items, or `(size_t)-1` (-1 cast to unsigned) on failure
 * \param dynarr the array to get the logical size of
 */
size_t NXS_DynamicArrayCount(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayTypeSize
 * returns the submitted typesize
 * \returns the typesize
 * \param dynarr the array to get the typesize from
 */
size_t NXS_DynamicArrayTypeSize(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayClear
 * sets all items to a binary value of `0x00`, but doesnt deallocate, leaving the capacity the same, but the count at 0
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to clear
 */
bool NXS_DynamicArrayClear(NXS_DynamicArray* dynarr);

/** NXS_DynamicArraySort
 * sorts the data using a provided function
 * \param dynarr the array to sort
 * \param compfunc the fucntion to use to decide which item should come after which,
 * for details see `qsort` and `__compar_fn_t` from `stdlib.h` from LibC,
 * this header also provides 'standard' functions for sorting to submit,
 * one for each standard typesize (8, 16, 32 and 64 bit) to sort based on pure, direct binary value,
 * these are: `NXS_DynamicArrayStdCompFunc8`, `NXS_DynamicArrayStdCompFunc16`,
 * `NXS_DynamicArrayStdCompFunc32` and `NXS_DynamicArrayStdCompFunc64` respecively
 * 
 * \sa NXS_DynamicArrayStdCompFunc8
 * \sa NXS_DynamicArrayStdCompFunc16
 * \sa NXS_DynamicArrayStdCompFunc32
 * \sa NXS_DynamicArrayStdCompFunc64
 */
void NXS_DynamicArraySort(NXS_DynamicArray* dynarr, __compar_fn_t compfunc);

/** NXS_DynamicArrayStdCompFunc8
 * is as standard sorting protocal for arrays with a typesize of `8`,
 * it sorts based on pure binary value, small (at index 0) to large,
 * e.g. `0b00010101` would come after `0b00010100`
 * \returns as specified for `__compar_fn_t`:
 * a negative for a before b,
 * positive for a after b
 * and 0 for to see a and b as equal
 * \param a one of the two items to compare
 * \param b the other item to compare
 */
int NXS_DynamicArrayStdCompFunc8(const void* a, const void* b);

/** NXS_DynamicArrayStdCompFunc16
 * is as standard sorting protocal for arrays with a typesize of `16`,
 * it sorts based on pure binary value, small (at index 0) to large,
 * e.g. `0xf001` would come after `0xf000`
 * \returns as specified for `__compar_fn_t`:
 * a negative for a before b,
 * positive for a after b
 * and 0 for to see a and b as equal
 * \param a one of the two items to compare
 * \param b the other item to compare
 */
int NXS_DynamicArrayStdCompFunc16(const void* a, const void* b);

/** NXS_DynamicArrayStdCompFunc32
 * is as standard sorting protocal for arrays with a typesize of `32`,
 * it sorts based on pure binary value, small (at index 0) to large,
 * e.g. `0x00f00001` would come after `0x00f00000`
 * \returns as specified for `__compar_fn_t`:
 * a negative for a before b,
 * positive for a after b
 * and 0 for to see a and b as equal
 * \param a one of the two items to compare
 * \param b the other item to compare
 */
int NXS_DynamicArrayStdCompFunc32(const void* a, const void* b);

/** NXS_DynamicArrayStdCompFunc64
 * is as standard sorting protocal for arrays with a typesize of `64`,
 * it sorts based on pure binary value, small (at index 0) to large,
 * e.g. `0x0000000000f00001` would come after `0x0000000000f00000`
 * \returns as specified for `__compar_fn_t`:
 * a negative for a before b,
 * positive for a after b
 * and 0 for to see a and b as equal
 * \param a one of the two items to compare
 * \param b the other item to compare
 * 
 * \note this function (unlike the smaller size versions,
 * which are implemented by type punning to a uint of the given size,
 * and subtracting to find the difference as a negative, positive or zero directly),
 * this funcion uses if statements,
 * to avoid an overflow of the return `int` with the 64 bit result,
 * possibly adding a VERY VERY minimal overhead
 */
int NXS_DynamicArrayStdCompFunc64(const void* a, const void* b);

/** NXS_DynamicArrayResize
 * changes the capacity (and reallocates), deallocating and removing any if the new capacity is less than the logical size/count
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to resize
 * \param new_size the size to resize to
 * 
 * \note two more safely 'reserve' space, use `NXS_DynamicArrayReserve`,
 * which will only reallocate to a greater value, and is a few instructions faster
 * \sa NXS_DynamicArrayReserve
 */
bool NXS_DynamicArrayResize(NXS_DynamicArray* dynarr, size_t new_size);

/** NXS_DynamicArrayReserve
 * reallocates a array to increase the capacity by the provided `space_count`,
 * to minimize the possability of reallocations in a push opperation,
 * for optimization
 * \returns `true` on success, or `false` on failure
 * \param dynarr the array to reserve space in
 * \param space_count the amount of spaces to reserve
 * \sa NXS_DynamicArrayResize
 */
bool NXS_DynamicArrayReserve(NXS_DynamicArray* dynarr, size_t space_count);

/** NXS_DynamicArrayEmpty
 * check if all allocated spaces are empty
 * \returns `true` if the provided array is empty, or `false` if it is not
 * \param dynarr the array to check
 */
bool NXS_DynamicArrayEmpty(NXS_DynamicArray* dynarr);

/** NXS_DynamicArrayPoll
 * returns and removes the front item, for use as queue
 * \returns `false` on error or if just returned the last item in the array, `true` if the array still has remaining members
 * \param dynarr the array to poll
 * \param out a `void` pointer to use as buffer for the returned item,
 * NEEDS TO BE ALLOCATED BEFOREHAND (is copied with `memcpy`)
 * \note this funciton internally uses a itterator stored in the dynamic array,
 * this means that the poll operation will not shift any members (for efficiency),
 * but this also means that if you call any dynamic array function before having reached the end,
 * that function will proform a shift to allign the array
 */
bool NXS_DynamicArrayPoll(NXS_DynamicArray* dynarr, void* out);

#endif //NXS_DYNAMIC_ARRAY_H