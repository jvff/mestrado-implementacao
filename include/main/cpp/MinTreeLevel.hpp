#ifndef MIN_TREE_LEVEL_HPP
#define MIN_TREE_LEVEL_HPP

#include <functional>

#include "MinMaxTreeLevel.hpp"

template <typename T>
using MinTreeLevel = MinMaxTreeLevel<T, std::greater<T> >;

#endif
