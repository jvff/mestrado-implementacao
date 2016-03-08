#ifndef FAKE_MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP
#define FAKE_MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP

#include "MinMaxTreeImageFilterImplementation.hpp"

template <typename InternalImageType, typename LevelOrderComparator>
class FakeMinMaxTreeImageFilterImplementation
        : public MinMaxTreeImageFilterImplementation<InternalImageType,
                LevelOrderComparator> {
private:
    using ImageType = MinMaxTreeImage<InternalImageType, LevelOrderComparator>;
    using SuperClass = MinMaxTreeImageFilterImplementation<InternalImageType,
            LevelOrderComparator>;

public:
    using SuperClass::sourceImage;

public:
    FakeMinMaxTreeImageFilterImplementation(const ImageType& sourceImage,
            ImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
    }

    using SuperClass::collectPixelNodes;
    using SuperClass::getLeafNodesIn;
};

#endif
