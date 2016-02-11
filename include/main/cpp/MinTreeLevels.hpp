#ifndef MIN_TREE_LEVELS_HPP
#define MIN_TREE_LEVELS_HPP

#include <functional>

#include "MinMaxTreeLevels.hpp"

template <typename T>
using MinTreeLevels = MinMaxTreeLevels<T, std::greater<T> >;

#endif
