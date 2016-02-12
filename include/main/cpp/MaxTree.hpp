#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

#include <functional>

#include "MinMaxTree.hpp"

template <typename T>
using MaxTree = MinMaxTree<T, std::less<T> >;

#endif
