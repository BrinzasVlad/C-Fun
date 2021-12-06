#ifndef DIRECT_SORTING_INCLUDED
#define DIRECT_SORTING_INCLUDED

#include "../0. Utils/MeasurementUtils.hpp" // OperationCounter
#include <functional> // std::less
#include <iterator> // std::iterator_traits

template <typename RandomAccessIterator, typename Compare>
void insertionSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count = NULL);

template <typename RandomAccessIterator>
void insertionSort (const RandomAccessIterator first, const RandomAccessIterator last, OperationCounter* count = NULL) {
    insertionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>(), count);
}

template <typename RandomAccessIterator, typename Compare>
void selectionSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count = NULL);

template <typename RandomAccessIterator>
void selectionSort (const RandomAccessIterator first, const RandomAccessIterator last, OperationCounter* count = NULL) {
    selectionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>(), count);
}

template <typename RandomAccessIterator, typename Compare>
void bubbleSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count = NULL);

template <typename RandomAccessIterator>
void bubbleSort (const RandomAccessIterator first, const RandomAccessIterator last, OperationCounter* count = NULL) {
    bubbleSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>(), count);
}

#include "DirectSort.tpp"

#endif // DIRECT_SORTING_INCLUDED
