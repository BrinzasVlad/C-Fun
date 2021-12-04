#ifndef ARRAY_UTILS_INCLUDED
#define ARRAY_UTILS_INCLUDED

#include <vector>

enum class Sorted { Unsorted, Ascending, Descending };
std::vector<int> randomIntVector(int size, Sorted sorted = Sorted::Unsorted, int low = 0, int high = 1000000);

#endif // ARRAY_UTILS_INCLUDED
