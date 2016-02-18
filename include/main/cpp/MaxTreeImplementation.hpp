#ifndef MAX_TREE_IMPLEMENTATION_HPP
#define MAX_TREE_IMPLEMENTATION_HPP

#include <functional>

#include "MinMaxTreeImplementation.hpp"

template <typename SourceImageType, typename InternalImageType>
using MaxTreeImplementation = MinMaxTreeImplementation<SourceImageType,
        InternalImageType, std::less>;

#endif
