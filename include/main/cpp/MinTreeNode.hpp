#ifndef MIN_TREE_NODE_HPP
#define MIN_TREE_NODE_HPP

#include <functional>

#include "MinMaxTreeNode.hpp"

template <typename T>
using MinTreeNode = MinMaxTreeNode<T, std::greater<T> >;

#endif
