#ifndef FILTER_HPP
#define FILTER_HPP

#include "AbstractFilter.hpp"
#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType>
class Filter : public AbstractFilter<SourceImageType, DestinationImageType> {
protected:
    DestinationImageType createDestinationImage(
            const SourceImageType& sourceImage) override {
        auto width = getDestinationImageWidth(sourceImage);
        auto height = getDestinationImageHeight(sourceImage);

        return DestinationImageType(width, height);
    }

    virtual unsigned int getDestinationImageWidth(
            const SourceImageType& sourceImage) {
        return sourceImage.getWidth();
    }

    virtual unsigned int getDestinationImageHeight(
            const SourceImageType& sourceImage) {
        return sourceImage.getHeight();
    }
};

#endif
