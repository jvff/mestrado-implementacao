#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

template <typename T>
class MaxTree {
private:
    bool empty = true;

public:
    bool isEmpty() {
        return empty;
    }

    void addNode(const T&) {
        empty = false;
    }

    void removeNode(const T&, unsigned int) {
        empty = true;
    }
};

#endif
