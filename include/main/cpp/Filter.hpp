#ifndef FILTER_HPP
#define FILTER_HPP

#include "AbstractFilter.hpp"
#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType>
class Filter : public AbstractFilter<SourceImageType, DestinationImageType> {
public:
    virtual ~Filter() {
    }

    virtual DestinationImageType apply(const SourceImageType& sourceImage) {
        auto destinationImage = createDestinationImage(sourceImage);

        apply(sourceImage, destinationImage);

        return destinationImage;
    }

    virtual void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) = 0;

protected:
    virtual unsigned int getDestinationImageWidth(
            const SourceImageType& sourceImage) {
        return sourceImage.getWidth();
    }

    virtual unsigned int getDestinationImageHeight(
            const SourceImageType& sourceImage) {
        return sourceImage.getHeight();
    }

    virtual DestinationImageType createDestinationImage(
            const SourceImageType& sourceImage) {
        auto width = getDestinationImageWidth(sourceImage);
        auto height = getDestinationImageHeight(sourceImage);

        return DestinationImageType(width, height);
    }
};

#endif
