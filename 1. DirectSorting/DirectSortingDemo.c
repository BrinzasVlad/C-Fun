/*
 Objectives:
 - Implement Bubble Sort, Selection Sort and Insertion Sort (with binary insertion)
 - Compare the complexity (in terms of comparisons and assignments) for best case, worst case and average case for [100...10000] elements
 - Discuss efficiency and stability for the presented approaches
*/

#include <stdio.h> // printf
#include <stdlib.h> // free, srand
#include <time.h> // time
#include "../0. Utilities/RandomGenerator.h" // generateRandomIntegerArray
#include "../0. Utilities/MemoryOperations.h" // copyArray
#include "DirectSorting.h"

int compareInts(void* first, void* second) {
    return *((int*)first) - *((int*)second);
}

int* generateBestCaseArray(int numElements) {
    // For all three algorithms, the best case array is an already-sorted one
    int* bestCaseArray = (int*)malloc(numElements * sizeof(int));

    for (int i = 0; i < numElements; ++i) {
        bestCaseArray[i] = i + 1;
    }

    return bestCaseArray;
}

int* generateWorstCaseSelection(int numElements) {
    // Worst case for selection sort is highest element first, then a sorted array
    int* worstCaseArray = (int*)malloc(numElements * sizeof(int));

    worstCaseArray[0] = numElements;
    for (int i = 1; i < numElements; ++i) {
        worstCaseArray[i] = i;
    }

    return worstCaseArray;
}

int* generateWorstCaseBubbleInsertion(int numElements) {
    // Worst case for insertion sort and bubble sort is a reverse-sorted array
    int* worstCaseArray = (int*)malloc(numElements * sizeof(int));

    for (int i = 0; i < numElements; ++i) {
        worstCaseArray[i] = numElements - i;
    }

    return worstCaseArray;
}

void demoSelectionSort(int* arrayToDemo, int numberOfElements) {
    int* selectionSortCopy = (int*)copyArray((void*)arrayToDemo, sizeof(int), numberOfElements);

    totalOperations selectionSortOperations = selectionSort(selectionSortCopy, numberOfElements, sizeof(int), compareInts);

    printf("\nThe array, as sorted by selection sort, is now:\n");
    for (int i = 0; i < numberOfElements; ++i) printf("%d ", selectionSortCopy[i]);
    printf("\n");

    printf("The sorting required %d comparisons and %d assignments.\n",
           selectionSortOperations.comparisons,
           selectionSortOperations.assignments);

    free(selectionSortCopy);
}

void demoInsertionSort(int* arrayToDemo, int numberOfElements) {
    int* insertionSortCopy = (int*)copyArray((void*)arrayToDemo, sizeof(int), numberOfElements);

    totalOperations insertionSortOperations = insertionSort(insertionSortCopy, numberOfElements, sizeof(int), compareInts);

    printf("\nThe array, as sorted by insertion sort, is now:\n");
    for (int i = 0; i < numberOfElements; ++i) printf("%d ", insertionSortCopy[i]);
    printf("\n");

    printf("The sorting required %d comparisons and %d assignments.\n",
           insertionSortOperations.comparisons,
           insertionSortOperations.assignments);

    free(insertionSortCopy);
}

void demoBubbleSort(int* arrayToDemo, int numberOfElements) {
    int* bubbleSortCopy = (int*)copyArray((void*)arrayToDemo, sizeof(int), numberOfElements);

    totalOperations bubbleSortOperations = bubbleSort(bubbleSortCopy, numberOfElements, sizeof(int), compareInts);

    printf("\nThe array, as sorted by bubble sort, is now:\n");
    for (int i = 0; i < numberOfElements; ++i) printf("%d ", bubbleSortCopy[i]);
    printf("\n");

    printf("The sorting required %d comparisons and %d assignments.\n",
           bubbleSortOperations.comparisons,
           bubbleSortOperations.assignments);

    free(bubbleSortCopy);
}

void demoAverageCase(int demoSize) {
    int* arrayToSort = generateRandomIntegerArray(demoSize, 0, 50);

    printf("[-- Average case --]\n");

    printf("\n - We have generated the following random array for demonstration:\n");
    for (int i = 0; i < demoSize; ++i) printf("%d ", arrayToSort[i]);
    printf("\n");

    demoSelectionSort(arrayToSort, demoSize);

    demoInsertionSort(arrayToSort, demoSize);

    demoBubbleSort(arrayToSort, demoSize);

    free(arrayToSort);
}

void demoBestCase(int demoSize) {
    int* arrayToSort = generateBestCaseArray(demoSize);

    printf("\n[-- Best Case --]\n");

    printf("\n - The best-case array for all algorithms is an already-sorted one:\n");
    for (int i = 0; i < demoSize; ++i) printf("%d ", arrayToSort[i]);
    printf("\n");

    demoSelectionSort(arrayToSort, demoSize);

    demoInsertionSort(arrayToSort, demoSize);

    demoBubbleSort(arrayToSort, demoSize);

    free(arrayToSort);
}

void demoWorstCase(int demoSize) {
    int* arrayToSortSelection = generateWorstCaseSelection(demoSize);
    int* arrayToSortBubbleInsertion = generateWorstCaseBubbleInsertion(demoSize);

    printf("\n[-- Worst Case --]\n");

    printf("\n - The worst-case array for selection sort is highest element first, followed by a sorted array:\n");
    for (int i = 0; i < demoSize; ++i) printf("%d ", arrayToSortSelection[i]);
    printf("\n");

    demoSelectionSort(arrayToSortSelection, demoSize);

    printf("\n - The worst-case array for insertion sort and bubble sort is an array sorted in descending order:\n");
    for (int i = 0; i < demoSize; ++i) printf("%d ", arrayToSortBubbleInsertion[i]);
    printf("\n");

    demoInsertionSort(arrayToSortBubbleInsertion, demoSize);

    demoBubbleSort(arrayToSortBubbleInsertion, demoSize);

    free(arrayToSortSelection);
    free(arrayToSortBubbleInsertion);
}

typedef struct {
    int bubbleAssignments;
    int bubbleComparisons;
    int insertionAssignments;
    int insertionComparisons;
    int selectionAssignments;
    int selectionComparisons;
} sortComparisonResults;

sortComparisonResults computeAverageCase(int numElements, int repetitionsForAverage) {
    sortComparisonResults results = {}; // Default all to 0

    for (int repetition = 0; repetition < repetitionsForAverage; ++repetition) {
        int* arrayToSort = generateRandomIntegerArray(numElements, 0, 30000); // Allow for some equal elements

        // Bubble Sort
        int* bubbleSortCopy = copyArray(arrayToSort, sizeof(int), numElements);
        totalOperations bubbleSortOneRun = bubbleSort(bubbleSortCopy, numElements, sizeof(int), compareInts);
        results.bubbleAssignments += bubbleSortOneRun.assignments;
        results.bubbleComparisons += bubbleSortOneRun.comparisons;
        free(bubbleSortCopy);

        // Selection Sort
        int* selectionSortCopy = copyArray(arrayToSort, sizeof(int), numElements);
        totalOperations selectionSortOneRun = selectionSort(selectionSortCopy, numElements, sizeof(int), compareInts);
        results.selectionAssignments += selectionSortOneRun.assignments;
        results.selectionComparisons += selectionSortOneRun.comparisons;
        free(selectionSortCopy);

        // Insertion Sort
        int* insertionSortCopy = copyArray(arrayToSort, sizeof(int), numElements);
        totalOperations insertionSortOneRun = insertionSort(insertionSortCopy, numElements, sizeof(int), compareInts);
        results.insertionAssignments += insertionSortOneRun.assignments;
        results.insertionComparisons += insertionSortOneRun.comparisons;
        free(insertionSortCopy);

        // Free main array; TODO: it would be more efficient to allocate once and then overwrite
        free(arrayToSort);
    }

    // Adjust so we get an average, not a sum
    results.bubbleAssignments /= repetitionsForAverage;
    results.bubbleComparisons /= repetitionsForAverage;
    results.selectionAssignments /= repetitionsForAverage;
    results.selectionComparisons /= repetitionsForAverage;
    results.insertionAssignments /= repetitionsForAverage;
    results.insertionComparisons /= repetitionsForAverage;

    return results;
}

sortComparisonResults computeBestCase(int numElements) {
    sortComparisonResults results = {}; // Default all to 0

    // Bubble Sort
    int* bubbleSortCopy = generateBestCaseArray(numElements);
    totalOperations bubbleSortOneRun = bubbleSort(bubbleSortCopy, numElements, sizeof(int), compareInts);
    results.bubbleAssignments += bubbleSortOneRun.assignments;
    results.bubbleComparisons += bubbleSortOneRun.comparisons;
    free(bubbleSortCopy);

    // Selection Sort
    int* selectionSortCopy = generateBestCaseArray(numElements);
    totalOperations selectionSortOneRun = selectionSort(selectionSortCopy, numElements, sizeof(int), compareInts);
    results.selectionAssignments += selectionSortOneRun.assignments;
    results.selectionComparisons += selectionSortOneRun.comparisons;
    free(selectionSortCopy);

    // Insertion Sort
    int* insertionSortCopy = generateBestCaseArray(numElements);
    totalOperations insertionSortOneRun = insertionSort(insertionSortCopy, numElements, sizeof(int), compareInts);
    results.insertionAssignments += insertionSortOneRun.assignments;
    results.insertionComparisons += insertionSortOneRun.comparisons;
    free(insertionSortCopy);

    return results;
}

sortComparisonResults computeWorstCase(int numElements) {
    sortComparisonResults results = {}; // Default all to 0

    // Bubble Sort
    int* bubbleSortCopy = generateWorstCaseBubbleInsertion(numElements);
    totalOperations bubbleSortOneRun = bubbleSort(bubbleSortCopy, numElements, sizeof(int), compareInts);
    results.bubbleAssignments += bubbleSortOneRun.assignments;
    results.bubbleComparisons += bubbleSortOneRun.comparisons;
    free(bubbleSortCopy);

    // Selection Sort
    int* selectionSortCopy = generateWorstCaseSelection(numElements);
    totalOperations selectionSortOneRun = selectionSort(selectionSortCopy, numElements, sizeof(int), compareInts);
    results.selectionAssignments += selectionSortOneRun.assignments;
    results.selectionComparisons += selectionSortOneRun.comparisons;
    free(selectionSortCopy);

    // Insertion Sort
    int* insertionSortCopy = generateWorstCaseBubbleInsertion(numElements);
    totalOperations insertionSortOneRun = insertionSort(insertionSortCopy, numElements, sizeof(int), compareInts);
    results.insertionAssignments += insertionSortOneRun.assignments;
    results.insertionComparisons += insertionSortOneRun.comparisons;
    free(insertionSortCopy);

    return results;
}

void gatherStatisticalData(int numberOfElementsMin, int numberOfElementsMax, int numberOfElementsStep, int repetitionsForAverage) {
    char outFileName[] = "Direct Sorting.csv";

    printf("\nThe program is now computing time complexity estimates for each algorithm.\n");
    printf("The total assignments and comparisons (for average, best and worst case) will be gathered in '%s'\n", outFileName);

    FILE* outFile = fopen(outFileName, "w");
    fprintf(outFile, "Number of Elements, ");
    fprintf(outFile, "Assignments (Bubble) (Average), Comparisons (Bubble) (Average), Assignments + Comparisons (Bubble) (Average), ");
    fprintf(outFile, "Assignments (Selection) (Average), Comparisons (Selection) (Average), Assignments + Comparisons (Selection) (Average), ");
    fprintf(outFile, "Assignments (Insertion) (Average), Comparisons (Insertion) (Average), Assignments + Comparisons (Insertion) (Average),");
    fprintf(outFile, "Assignments (Bubble) (Best), Comparisons (Bubble) (Best), Assignments + Comparisons (Bubble) (Best), ");
    fprintf(outFile, "Assignments (Selection) (Best), Comparisons (Selection) (Best), Assignments + Comparisons (Selection) (Best), ");
    fprintf(outFile, "Assignments (Insertion) (Best), Comparisons (Insertion) (Best), Assignments + Comparisons (Insertion) (Best), ");
    fprintf(outFile, "Assignments (Bubble) (Worst), Comparisons (Bubble) (Worst), Assignments + Comparisons (Bubble) (Worst), ");
    fprintf(outFile, "Assignments (Selection) (Worst), Comparisons (Selection) (Worst), Assignments + Comparisons (Selection) (Worst), ");
    fprintf(outFile, "Assignments (Insertion) (Worst), Comparisons (Insertion) (Worst), Assignments + Comparisons (Insertion) (Worst)\n");

    for (int numElements = numberOfElementsMin; numElements <= numberOfElementsMax; numElements += numberOfElementsStep) {
        printf("Computing values for an array of %d elements...", numElements);
        fprintf(outFile, "%d, ", numElements);

        // Average Case
        printf(" Average case...");
        sortComparisonResults averageResults = computeAverageCase(numElements, repetitionsForAverage);

        fprintf(outFile, "%d, %d, ", averageResults.bubbleAssignments, averageResults.bubbleComparisons);
        fprintf(outFile, "%d, ", averageResults.bubbleAssignments + averageResults.bubbleComparisons);
        fprintf(outFile, "%d, %d, ", averageResults.selectionAssignments, averageResults.selectionComparisons);
        fprintf(outFile, "%d, ", averageResults.selectionAssignments + averageResults.selectionComparisons);
        fprintf(outFile, "%d, %d, ", averageResults.insertionAssignments, averageResults.insertionComparisons);
        fprintf(outFile, "%d, ", averageResults.insertionAssignments + averageResults.insertionComparisons);

        // Best Case
        printf(" Best case...");
        sortComparisonResults bestResults = computeBestCase(numElements);

        fprintf(outFile, "%d, %d, ", bestResults.bubbleAssignments, bestResults.bubbleComparisons);
        fprintf(outFile, "%d, ", bestResults.bubbleAssignments + bestResults.bubbleComparisons);
        fprintf(outFile, "%d, %d, ", bestResults.selectionAssignments, bestResults.selectionComparisons);
        fprintf(outFile, "%d, ", bestResults.selectionAssignments + bestResults.selectionComparisons);
        fprintf(outFile, "%d, %d, ", bestResults.insertionAssignments, bestResults.insertionComparisons);
        fprintf(outFile, "%d, ", bestResults.insertionAssignments + bestResults.insertionComparisons);

        // Worst Case
        printf(" Worst case...");
        sortComparisonResults worstResults = computeWorstCase(numElements);

        fprintf(outFile, "%d, %d, ", worstResults.bubbleAssignments, worstResults.bubbleComparisons);
        fprintf(outFile, "%d, ", worstResults.bubbleAssignments + worstResults.bubbleComparisons);
        fprintf(outFile, "%d, %d, ", worstResults.selectionAssignments, worstResults.selectionComparisons);
        fprintf(outFile, "%d, ", worstResults.selectionAssignments + worstResults.selectionComparisons);
        fprintf(outFile, "%d, %d, ", worstResults.insertionAssignments, worstResults.insertionComparisons);
        fprintf(outFile, "%d\n", worstResults.insertionAssignments + worstResults.insertionComparisons);

        printf(" Done.\n");
    }
}

int main() {
    const int DEMO_SIZE = 15;
    const int NUM_ELEMENTS_MIN = 100;
    const int NUM_ELEMENTS_MAX = 10000;
    const int NUM_ELEMENTS_STEP = 100;
    const int REPETITIONS_FOR_AVERAGE = 5;

    srand(time(NULL));

    demoAverageCase(DEMO_SIZE);
    demoBestCase(DEMO_SIZE);
    demoWorstCase(DEMO_SIZE);

    gatherStatisticalData(NUM_ELEMENTS_MIN, NUM_ELEMENTS_MAX, NUM_ELEMENTS_STEP, REPETITIONS_FOR_AVERAGE);

    return 0;
}
