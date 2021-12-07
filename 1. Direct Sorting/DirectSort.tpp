#include "../0. Utils/MeasurementUtils.hpp" // OperationCounter
#include <utility> // std::swap, std::move
#include <iterator> // std::iterator_traits

template <typename RandomAccessIterator, typename Compare>
void insertionSort (const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count) {

    // Start with one element sorted
    // Insert further elements into sorted part at the start of the array
    for (RandomAccessIterator firstUnsorted = first + 1; firstUnsorted < last; firstUnsorted++) {

        // Find position in sorted part where element should be inserted
        // We use an open-closed range ( [first, firstUnsorted) ), like the sort itself
        RandomAccessIterator searchLow = first, searchHigh = firstUnsorted;
        while (searchLow < searchHigh) {
            RandomAccessIterator searchMiddle = searchLow + (searchHigh - searchLow) / 2;

            // If smaller (or equal, for stability), search to the right
            // If greater, search to the left
            if (NULL != count) count->comparisons++;
            if (comp(*firstUnsorted, *searchMiddle)) {
                // If current element larger than the one to be inserted,
                // search further to the left
                searchHigh = searchMiddle;
            } else {
                // If current element smaller (or equal, for stability) than
                // the one to be inserted, search further to the right
                searchLow = searchMiddle + 1;
            }
        }
        RandomAccessIterator targetPosition = searchHigh;

        // Shift sorted part to insert element
        if (targetPosition != firstUnsorted) {
            if (NULL != count) count->assignments++;
            typename std::iterator_traits<RandomAccessIterator>::value_type temp = std::move(*firstUnsorted);

            for (RandomAccessIterator i = firstUnsorted; i > targetPosition; i--) {
                if (NULL != count) count->assignments++;
                *i = std::move(*(i-1));
            }

            if (NULL != count) count->assignments++;
            *targetPosition = std::move(temp);
        }
    }
}

template <typename RandomAccessIterator, typename Compare>
void selectionSort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count) {

    // Start with no elements sorted
    // Accumulate sorted elements at the start of the array
    for(RandomAccessIterator firstUnsorted = first; firstUnsorted < last - 1; firstUnsorted++) {

        // Find smallest unsorted element
        RandomAccessIterator min = firstUnsorted;
        for (RandomAccessIterator i = firstUnsorted + 1; i < last; ++i) {
            if (NULL != count) count->comparisons++;
            if (comp(*i, *min)) min = i;
        }

        // Place it at the end of the sorted portion
        if (min != firstUnsorted) {
            if (NULL != count) count->assignments += 3;
            std::swap(*min, *firstUnsorted);
        }
    }
}

template <typename RandomAccessIterator, typename Compare>
void bubbleSort(const RandomAccessIterator first, const RandomAccessIterator last, const Compare comp, OperationCounter* count) {

    // Start with no elements sorted
    // Bubble sorted elements up to the end of the array
    bool didAtLeastOneSwap = false;
    RandomAccessIterator lastUnsorted = last;
    do {
        // Bubble up, swapping smaller elements down
        for (RandomAccessIterator i = first; i < lastUnsorted - 1; i++) {
            if (NULL != count) count->comparisons++;
            if (comp(*(i+1), *i)) {
                didAtLeastOneSwap = true;
                if (NULL != count) count->assignments += 3;
                std::swap(*i, *(i+1));
            }
        }
        lastUnsorted--;

        // If no elements were swapped, array is sorted
        // Else, continue sorting
    } while (didAtLeastOneSwap && (lastUnsorted - 1 > first));
}
