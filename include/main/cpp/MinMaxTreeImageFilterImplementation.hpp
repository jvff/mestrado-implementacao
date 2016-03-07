#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "MinMaxTreeImage.hpp"

template <typename InternalImageType, typename LevelOrderComparator>
class MinMaxTreeImageFilterImplementation : public FilterImplementation<
        MinMaxTreeImage<InternalImageType, LevelOrderComparator>,
        MinMaxTreeImage<InternalImageType, LevelOrderComparator> > {
};

#endif
