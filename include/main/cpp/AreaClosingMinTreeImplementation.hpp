#ifndef AREA_CLOSING_MIN_TREE_IMPLEMENTATION_HPP
#define AREA_CLOSING_MIN_TREE_IMPLEMENTATION_HPP

#include <functional>

#include "AreaOpeningAndClosingMinMaxTreeImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
using AreaClosingMinTreeImplementation =
        AreaOpeningAndClosingMinMaxTreeImplementation<SourceImageType,
                DestinationImageType, std::greater>;

#endif
