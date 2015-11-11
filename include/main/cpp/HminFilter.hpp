#ifndef HMIN_FILTER_HPP
#define HMIN_FILTER_HPP

#include "ComplexFilter.hpp"
#include "HminImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HminFilter : public ComplexFilter<SourceImageType, DestinationImageType,
        HminImplementation<SourceImageType, DestinationImageType> > {
};

#endif
