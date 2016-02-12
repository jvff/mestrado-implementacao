#ifndef MIN_TREE_HPP
#define MIN_TREE_HPP

#include <functional>

#include "MinMaxTree.hpp"

template <typename T>
using MinTree = MinMaxTree<T, std::greater<T> >;

#endif
