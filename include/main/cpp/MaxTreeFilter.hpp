#ifndef MAX_TREE_FILTER_HPP
#define MAX_TREE_FILTER_HPP

#include <functional>

#include "MinMaxTreeFilter.hpp"

template <typename SourceImageType, typename InternalImageType>
using MaxTreeFilter = MinMaxTreeFilter<SourceImageType, InternalImageType,
        std::less>;

#endif
