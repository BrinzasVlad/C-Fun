#include <stdlib.h> // malloc
#include "RandomGenerator.h"

int* generateRandomIntegerArray(int numElements, int elemMin, int elemMax) {
    int* randomArray = (int*)malloc(numElements * sizeof(int));
    for (int i = 0; i < numElements; ++i) {
        randomArray[i] = elemMin + rand() % (elemMax - elemMin + 1);
    }
    return randomArray;
}
