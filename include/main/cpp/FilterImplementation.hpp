#ifndef FILTER_IMPLEMENTATION_HPP
#define FILTER_IMPLEMENTATION_HPP

template <typename SourceImageType, typename DestinationImageType>
class FilterImplementation {
protected:
    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

    unsigned int width;
    unsigned int height;
    unsigned int maxX;
    unsigned int maxY;

public:
    FilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) : sourceImage(sourceImage),
            destinationImage(destinationImage) {
        width = destinationImage.getWidth();
        height = destinationImage.getHeight();
        maxX = width - 1;
        maxY = height - 1;
    }

    virtual void apply() = 0;
};

#endif
