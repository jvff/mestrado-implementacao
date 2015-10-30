#ifndef INVERSION_FILTER_HPP
#define INVERSION_FILTER_HPP

#include "ComplexFilter.hpp"
#include "InversionImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class InversionFilter
        : public ComplexFilter<SourceImageType, DestinationImageType,
                InversionImplementation<SourceImageType,
                        DestinationImageType> > {
};

#endif
