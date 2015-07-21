#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP

#include "Filter.hpp"

template <typename PixelType, class DestinationImageType,
        class SourceImageType = Image<PixelType> >
class MorphologicalReconstructionFilter
        : public Filter<PixelType, PixelType, DestinationImageType> {
protected:
    PixelType apply(unsigned int x, unsigned int y,
            const Image<PixelType>& sourceImage) {
        return sourceImage.getPixel(x, y);
    }
};

#endif
