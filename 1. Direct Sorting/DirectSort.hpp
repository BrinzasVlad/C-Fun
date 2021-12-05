#ifndef DIRECT_SORTING_INCLUDED
#define DIRECT_SORTING_INCLUDED

#include <functional> // std::less
#include <iterator> // std::iterator_traits

template <typename RandomAccessIterator, typename Compare>
void insertionSort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator first, RandomAccessIterator last) {
    insertionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <typename RandomAccessIterator, typename Compare>
void selectionSort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <typename RandomAccessIterator>
void selectionSort (RandomAccessIterator first, RandomAccessIterator last) {
    selectionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <typename RandomAccessIterator, typename Compare>
void bubbleSort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <typename RandomAccessIterator>
void bubbleSort (RandomAccessIterator first, RandomAccessIterator last) {
    bubbleSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

#include "DirectSort.tpp"

#endif // DIRECT_SORTING_INCLUDED
