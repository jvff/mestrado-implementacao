#ifndef EQUALS_COMPARATOR_HPP
#define EQUALS_COMPARATOR_HPP

template <typename T>
class EqualsComparator {
public:
    bool operator() (const T& first, const T& second) {
        return first == second;
    }
};

#endif
