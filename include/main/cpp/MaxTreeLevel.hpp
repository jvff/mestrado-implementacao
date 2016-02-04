#ifndef MAX_TREE_LEVEL_HPP
#define MAX_TREE_LEVEL_HPP

#include <functional>

#include "MinMaxTreeLevel.hpp"

template <typename T>
using MaxTreeLevel = MinMaxTreeLevel<T, std::less<T> >;

#endif
