#ifndef CFUN_RANDOM_ARRAY_GEN
#define CFUN_RANDOM_ARRAY_GEN

/**
 Generates an unsorted array of random positive integers, each integer having
 a value between elemMin and elemMax (inclusive).
 The array is dynamically allocated and should be freed by the user.
 Note that the function uses rand() and thus the user should seed the random
 generator using srand().
*/
int* generateRandomIntegerArray(int numElements, int elemMin, int elemMax);

#endif // CFUN_RANDOM_ARRAY_GEN
