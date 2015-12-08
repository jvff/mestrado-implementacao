#ifndef MAX_TREE_LEVEL_HPP
#define MAX_TREE_LEVEL_HPP

template <typename T>
class MaxTreeLevel {
private:
    bool empty = true;

public:
    MaxTreeLevel(const T&) {
    }

    bool isEmpty() {
        return empty;
    }

    void addNode() {
        empty = false;
    }
};

#endif
