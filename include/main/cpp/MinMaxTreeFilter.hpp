#ifndef MIN_MAX_TREE_FILTER_HPP
#define MIN_MAX_TREE_FILTER_HPP

#include "ComplexFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

template <typename SourceImageType, typename InternalImageType,
        template <typename> class TreeTypeComparator>
class MinMaxTreeFilter : public ComplexFilter<SourceImageType,
        MinMaxTreeImage<InternalImageType,
                TreeTypeComparator<typename InternalImageType::PixelType> >,
        MinMaxTreeImplementation<SourceImageType, InternalImageType,
                TreeTypeComparator> > {
};

#endif
