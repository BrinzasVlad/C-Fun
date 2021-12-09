#ifndef MEASUREMENT_UTILS_INCLUDED
#define MEASUREMENT_UTILS_INCLUDED

#include <utility> // std::swap, std::move

struct OperationCounter {
    int assignments = 0;
    int comparisons = 0;
};

template<typename Compare>
class CompareWrapper {
    const Compare comp;
    OperationCounter* const counter;
public:
    // Forward types from Compare
    typedef typename Compare::first_argument_type first_argument_type;
    typedef typename Compare::second_argument_type second_argument_type;
    typedef typename Compare::result_type result_type;

    CompareWrapper(Compare comp, OperationCounter* counter) : comp(comp), counter(counter) {};

    result_type operator() (const first_argument_type& x, const second_argument_type& y) const {
        if (nullptr != counter) counter->comparisons++;
        return comp(x, y);
    }
};

template<typename T>
class SwapWrapper {
    OperationCounter* const counter;
public:
    SwapWrapper(OperationCounter* counter) : counter(counter) {};

    void operator() (T& a, T& b) const {
        if (nullptr != counter) counter->assignments += 3;
        std::swap(a, b);
    }
};

template<typename T>
class MoveWrapper {
    OperationCounter* const counter;
public:
    MoveWrapper(OperationCounter* counter) : counter(counter) {};

    void operator() (T& from, T& to) const {
        if (nullptr != counter) counter->assignments++;
        to = std::move(from);
    }
};

#endif // MEASUREMENT_UTILS_INCLUDED
