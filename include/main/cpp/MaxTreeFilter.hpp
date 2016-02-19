#ifndef MAX_TREE_FILTER_HPP
#define MAX_TREE_FILTER_HPP

#include <functional>

#include "ComplexFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

template <typename SourceImageType, typename InternalImageType,
        template <typename> class TreeTypeComparator>
class MinMaxTreeFilter : public ComplexFilter<SourceImageType,
        MaxTreeImage<InternalImageType>, MaxTreeImplementation<SourceImageType,
                InternalImageType> > {
};

template <typename SourceImageType, typename InternalImageType>
using MaxTreeFilter = MinMaxTreeFilter<SourceImageType, InternalImageType,
        std::less>;

#endif
