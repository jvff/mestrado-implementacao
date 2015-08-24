#ifndef FILTER_IMPLEMENTATION_HPP
#define FILTER_IMPLEMENTATION_HPP

template <typename SourceImageType, typename DestinationImageType>
class FilterImplementation {
protected:
    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

public:
    FilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) : sourceImage(sourceImage),
            destinationImage(destinationImage) {
    }
};

#endif
