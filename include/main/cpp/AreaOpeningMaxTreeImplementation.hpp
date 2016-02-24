#ifndef AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP
#define AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP

#include <functional>

#include "AreaOpeningAndClosingMinMaxTreeImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
using AreaOpeningMaxTreeImplementation =
        AreaOpeningAndClosingMinMaxTreeImplementation<SourceImageType,
                DestinationImageType, std::less>;

#endif
