#ifndef MIN_TREE_IMPLEMENTATION_HPP
#define MIN_TREE_IMPLEMENTATION_HPP

#include <functional>

#include "MinMaxTreeImplementation.hpp"

template <typename SourceImageType, typename InternalImageType>
using MinTreeImplementation = MinMaxTreeImplementation<SourceImageType,
        InternalImageType, std::greater>;

#endif
