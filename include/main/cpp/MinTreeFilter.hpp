#ifndef MIN_TREE_FILTER_HPP
#define MIN_TREE_FILTER_HPP

#include <functional>

#include "MinMaxTreeFilter.hpp"

template <typename SourceImageType, typename InternalImageType>
using MinTreeFilter = MinMaxTreeFilter<SourceImageType, InternalImageType,
        std::greater>;

#endif
