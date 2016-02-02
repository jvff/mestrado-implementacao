#ifndef MAX_TREE_NODE_HPP
#define MAX_TREE_NODE_HPP

#include <functional>

#include "MinMaxTreeNode.hpp"

template <typename T>
using MaxTreeNode = MinMaxTreeNode<T, std::less<T> >;

#endif
