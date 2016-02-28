#ifndef HMIN_MIN_TREE_IMPLEMENTATION_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "MinTreeImage.hpp"

template <typename InternalImageType>
class HminMinTreeImplementation : public FilterImplementation<
        MinTreeImage<InternalImageType>, MinTreeImage<InternalImageType> > {
};

#endif
