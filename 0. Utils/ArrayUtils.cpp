#include "ArrayUtils.hpp"

#include <random> // std::random_device, std::default_random_engine, std::uniform_int_distribution
#include <algorithm> // std::sort
#include <functional> // std::greater

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
        std::sort(randomVector.begin(), randomVector.end(), std::greater<int>());
    }

    return randomVector;
}
