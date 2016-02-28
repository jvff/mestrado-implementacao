#ifndef HMIN_MIN_TREE_IMPLEMENTATION_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "MinTreeImage.hpp"

template <typename InternalImageType>
class HminMinTreeImplementation : public FilterImplementation<
        MinTreeImage<InternalImageType>, MinTreeImage<InternalImageType> > {
private:
    using ImageType = MinTreeImage<InternalImageType>;
    using PixelType = typename InternalImageType::PixelType;
    using SuperClass = FilterImplementation<ImageType, ImageType>;

public:
    HminMinTreeImplementation(const PixelType&, const ImageType& sourceImage,
            ImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
    }
};

#endif
