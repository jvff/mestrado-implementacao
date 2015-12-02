#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

template <typename T>
class MaxTree {
private:
    unsigned int nodes = 0u;

public:
    bool isEmpty() {
        return nodes == 0u;
    }

    unsigned int numberOfLevels() {
        return nodes;
    }

    void addNode(const T&) {
        ++nodes;
    }

    void removeNode(const T&, unsigned int) {
        --nodes;
    }
};

#endif
