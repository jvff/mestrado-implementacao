#ifndef ABSTRACT_FILTER_HPP
#define ABSTRACT_FILTER_HPP

template <typename SourceImageType, typename DestinationImageType>
class AbstractFilter {
public:
    virtual ~AbstractFilter() {
    }

    DestinationImageType apply(const SourceImageType& sourceImage) {
        auto destinationImage = createDestinationImage(sourceImage);

        apply(sourceImage, destinationImage);

        return destinationImage;
    }

    virtual void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) = 0;

protected:
    virtual DestinationImageType createDestinationImage(
            const SourceImageType& sourceImage) = 0;
};

#endif
