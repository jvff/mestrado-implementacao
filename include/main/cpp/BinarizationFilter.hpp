#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class BinarizationFilter : public Filter<SourcePixelType, bool,
        DestinationImageType, SourceImageType> {
protected:
    unsigned int getDestinationImageWidth(const SourceImageType*) {
        return 0;
    }

    unsigned int getDestinationImageHeight(const SourceImageType*) {
        return 0;
    }

    bool apply(unsigned int, unsigned int, const SourceImageType*) {
        return true;
    }
};

#endif
