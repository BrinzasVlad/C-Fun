#ifndef CFUN_DIRECT_SORTING
#define CFUN_DIRECT_SORTING

typedef struct {
    int comparisons;
    int assignments;
} totalOperations;

/**
 Sorts the given array of whatever elements in-place using Selection Sort.
 Expects a comparison function as last parameter, which should compare two elements and yield a negative number if the first one is
 smaller, 0 if the elements are equal and a positive number if the first one is larger. (An example of a such function for integers
 is (first - second).
 Expects the size of one element of the array as second-to-last element, as given by sizeof.
*/
totalOperations selectionSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*));

/**
 Sorts the given array of whatever elements in-place using binary-insert Insertion Sort.
 Expects a comparison function as last parameter, which should compare two elements and yield a negative number if the first one is
 larger, 0 if the elements are equal and a positive number if the first one is smaller. (An example of a such function for integers
 is (second - first).
 Expects the size of one element of the array as second-to-last element, as given by sizeof.
*/
totalOperations insertionSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*));

/**
 Sorts the given array of whatever elements in-place using Bubble Sort.
 Expects a comparison function as last parameter, which should compare two elements and yield a negative number if the first one is
 smaller, 0 if the elements are equal and a positive number if the first one is larger. (An example of a such function for integers
 is (first - second).
 Expects the size of one element of the array as second-to-last element, as given by sizeof.
*/
totalOperations bubbleSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*));

#endif // CFUN_DIRECT_SORTING
