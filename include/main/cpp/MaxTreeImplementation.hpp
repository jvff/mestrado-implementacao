#ifndef MAX_TREE_IMPLEMENTATION_HPP
#define MAX_TREE_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"

template <typename SourceImageType, typename InternalImageType>
class MaxTreeImplementation : public FilterImplementation<SourceImageType,
        MaxTreeImage<InternalImageType> > {
private:
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;

public:
    using SuperClass::SuperClass;

    void apply() override {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                auto pixelValue = sourceImage.getPixelValue(x, y);

                destinationImage.setPixel(x, y, pixelValue);
                destinationImage.assignPixelToLatestNode(x, y);
            }
        }
    }
};

#endif
