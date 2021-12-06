#ifndef DIRECT_SORTING_INCLUDED
#define DIRECT_SORTING_INCLUDED

#include <functional> // std::less
#include <iterator> // std::iterator_traits

template <typename RandomAccessIterator, typename Compare>
void insertionSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp);

template <typename RandomAccessIterator>
void insertionSort (const RandomAccessIterator first, const RandomAccessIterator last) {
    insertionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <typename RandomAccessIterator, typename Compare>
void selectionSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp);

template <typename RandomAccessIterator>
void selectionSort (const RandomAccessIterator first, const RandomAccessIterator last) {
    selectionSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <typename RandomAccessIterator, typename Compare>
void bubbleSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp);

template <typename RandomAccessIterator>
void bubbleSort (const RandomAccessIterator first, const RandomAccessIterator last) {
    bubbleSort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

#include "DirectSort.tpp"

#endif // DIRECT_SORTING_INCLUDED
