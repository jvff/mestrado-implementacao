#ifndef MAX_TREE_LEVELS_HPP
#define MAX_TREE_LEVELS_HPP

template <typename T>
class MaxTreeLevels {
public:
    bool isEmpty() const {
        return true;
    }

    unsigned int numberOfLevels() const {
        return 0u;
    }

    bool hasLevel(const T&) const {
        return false;
    }
};

#endif
