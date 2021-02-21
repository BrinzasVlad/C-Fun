#ifndef CFUN_MEMORY_OPERATIONS
#define CFUN_MEMORY_OPERATIONS

#include <stddef.h>

/**
 Swaps the values of two elements of whatever type.
 Expects as last argument the size of one element, as given by sizeof.
*/
void swapElements(void* first, void* second, size_t elementSize);

/**
 Returns a pointer to the index-th element in the array, type-agnostic.
 Equivalent of array[index] for void* arrays.
*/
void* elementAt(void* array, size_t elementSize, int index);

/**
 Returns a shallow (!) copy of an array of elements of whatever type.
 The new array is dynamically allocated and should be freed by the user.
*/
void* copyArray(void* arrayToCopy, size_t elementSize, int numberOfElements);

#endif // CFUN_MEMORY_OPERATIONS
