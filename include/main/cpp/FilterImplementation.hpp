#ifndef FILTER_IMPLEMENTATION_HPP
#define FILTER_IMPLEMENTATION_HPP

template <typename SourceImageType, typename DestinationImageType>
class FilterImplementation {
protected:
    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

    unsigned int width;
    unsigned int height;

public:
    FilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) : sourceImage(sourceImage),
            destinationImage(destinationImage) {
        width = destinationImage.getWidth();
        height = destinationImage.getHeight();
    }
};

#endif
