#include "ArrayUtils.hpp"

#include <random>
#include <algorithm>
#include <functional>

std::vector<int> randomIntVector(int size, Sorted sorted, int low, int high) {
    std::vector<int> randomVector (size);

    std::random_device rand;
    std::default_random_engine engine(rand());
    std::uniform_int_distribution<int> dist(low, high);

    for (int& el : randomVector) {
        el = dist(engine);
    }

    if (Sorted::Ascending == sorted) {
        std::sort(randomVector.begin(), randomVector.end());
    } else if (Sorted::Descending == sorted) {
        std::sort(randomVector.begin(), randomVector.end(), std::greater<>());
    }

    return randomVector;
}
