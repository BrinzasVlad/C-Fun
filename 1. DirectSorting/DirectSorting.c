#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdbool.h> // bool
#include "../0. Utilities/MemoryOperations.h" // elementAt, swapElements
#include "DirectSorting.h"

totalOperations selectionSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*)) {
    totalOperations operationsUsed = { .comparisons = 0, .assignments = 0 };

    // The very last element will be in place by the time we reach it, so we leave it be
    for (int i = 0; i < numberOfElements - 1; ++i) {
        int indexOfMinimum = i;

        for (int j = i + 1; j < numberOfElements; ++j) {
            operationsUsed.comparisons++;
            if (0 < compare(elementAt(arrayToSort, elementSize, indexOfMinimum),
                            elementAt(arrayToSort, elementSize, j))) {
                indexOfMinimum = j;
            }
        }

        if (indexOfMinimum != i) {
            operationsUsed.assignments += 3;
            swapElements(elementAt(arrayToSort, elementSize, i),
                         elementAt(arrayToSort, elementSize, indexOfMinimum),
                         elementSize);
        }
    }

    return operationsUsed;
}

// TODO: modifiable parameter "comparisons" is a hacky fix so we can actually count these
int findIndexToInsertAt(void* arrayToFindIn, int numberOfElements, size_t elementSize, void* elementToInsert, int (*compare)(void*, void*), int* comparisons) {
    int lowerBound = 0;
    int upperBound = numberOfElements - 1;

    int middle;
    do {
        middle = (lowerBound + upperBound) / 2; // Round down by default

        (*comparisons)++;
        int comparison = compare(elementToInsert, elementAt(arrayToFindIn, elementSize, middle));

        if (comparison < 0) {
            // Element too small, look to the left
            upperBound = middle - 1;
        } else if (comparison > 0) {
            // Element too large, look to the right
            lowerBound = middle + 1;
        } else {
            // Element exactly equal
            break;
        }
    } while (lowerBound <= upperBound);

    // We now find the first slot in the array greater than the element to be inserted
    // Or alternatively, run to the end of the array and insert it there
    while (middle < numberOfElements) {
        (*comparisons)++;
        if (0 <= compare(elementToInsert, elementAt(arrayToFindIn, elementSize, middle))) {
            middle++;
        } else {
            break;
        }
    }

    return middle;
}

totalOperations insertionSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*)) {
    totalOperations operationsUsed = { .comparisons = 0, .assignments = 0 };

    void* aux = malloc(elementSize);
    // We can consider the first element to already be well-arranged in the section we insert into
    for (int i = 1; i < numberOfElements; ++i) {
        int indexToInsertAt = findIndexToInsertAt(arrayToSort,
                                                  i, // All elements left of index i are in the well-arranged section
                                                  elementSize,
                                                  elementAt(arrayToSort, elementSize, i),
                                                  compare,
                                                  &(operationsUsed.comparisons));

        if (indexToInsertAt != i) {
            operationsUsed.assignments++;
            memcpy(aux, elementAt(arrayToSort, elementSize, i), elementSize);

            // Move all elements in the well-arranged section one to the right to make room for the new one
            for (int j = i; j > indexToInsertAt; --j) {
                operationsUsed.assignments++;
                memcpy(elementAt(arrayToSort, elementSize, j),
                       elementAt(arrayToSort, elementSize, j - 1),
                       elementSize);
            }

            operationsUsed.assignments++;
            memcpy(elementAt(arrayToSort, elementSize, indexToInsertAt), aux, elementSize);
        }
    }
    free(aux);

    return operationsUsed;
}

totalOperations bubbleSort(void* arrayToSort, int numberOfElements, size_t elementSize, int (*compare)(void*, void*)) {
    totalOperations operationsUsed = { .comparisons = 0, .assignments = 0 };

    bool arrayIsUnchanged;
    for (int i = 0; i < numberOfElements - 1; ++i) {
        // Each repetition sets the highest element at the end of the array via bubbling
        // So we need numberOfElements - 1 repetitions at most, since the last element will be sorted by default

        arrayIsUnchanged = true;

        for (int j = 0; j < numberOfElements - i - 1; j++) {
            operationsUsed.comparisons++;
            if (0 < compare(elementAt(arrayToSort, elementSize, j), elementAt(arrayToSort, elementSize, j + 1))) {
                operationsUsed.assignments += 3;
                swapElements(elementAt(arrayToSort, elementSize, j),
                             elementAt(arrayToSort, elementSize, j + 1),
                             elementSize);
                arrayIsUnchanged = false;
            }
        }

        if (arrayIsUnchanged) break; // The array happened to end up sorted sooner, so we can stop
    }

    return operationsUsed;
}
