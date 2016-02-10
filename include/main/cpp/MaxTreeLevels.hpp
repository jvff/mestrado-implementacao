#ifndef MAX_TREE_LEVELS_HPP
#define MAX_TREE_LEVELS_HPP

#include <functional>

#include "MinMaxTreeLevels.hpp"

template <typename T>
using MaxTreeLevels = MinMaxTreeLevels<T, std::less<T> >;

#endif
