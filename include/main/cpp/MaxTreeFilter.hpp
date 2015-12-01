#ifndef MAX_TREE_FILTER_HPP
#define MAX_TREE_FILTER_HPP

#include "ComplexFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

template <typename SourceImageType, typename InternalImageType>
class MaxTreeFilter : public ComplexFilter<SourceImageType,
        MaxTreeImage<InternalImageType>, MaxTreeImplementation<SourceImageType,
                InternalImageType> > {
};

#endif
