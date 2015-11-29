#ifndef MAX_TREE_IMPLEMENTATION_HPP
#define MAX_TREE_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"

template <typename SourceImageType, typename InternalImageType>
class MaxTreeImplementation : public FilterImplementation<SourceImageType,
        MaxTreeImage<InternalImageType> > {
};

#endif
