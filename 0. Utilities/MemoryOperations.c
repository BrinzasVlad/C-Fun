#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "MemoryOperations.h"

void swapElements(void* first, void* second, size_t elementSize) {
    void* aux = malloc(elementSize);
    memcpy(aux, first, elementSize);
    memcpy(first, second, elementSize);
    memcpy(second, aux, elementSize);
    free(aux);
}

void* elementAt(void* array, size_t elementSize, int index) {
    char* arrayPermittingPointerArithmetic = (char*)array;
    return (void*)(arrayPermittingPointerArithmetic + index * elementSize);
}

void* copyArray(void* arrayToCopy, size_t elementSize, int numberOfElements) {
    void* newArray = malloc(elementSize * numberOfElements);
    memcpy(newArray, arrayToCopy, elementSize * numberOfElements);
    return newArray;
}
