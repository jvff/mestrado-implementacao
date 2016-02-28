#ifndef HMIN_IMPLEMENTATION_TEST_HPP
#define HMIN_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "../AbstractFilterImplementationTestData.hpp"
#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#include "HminTestData.hpp"

class HminImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = HminImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class HminImplementationTestData : public AbstractFilterImplementationTestData<
                HminImplementation<ImageType, ImageType>, ImageType,
                ImageType> {
private:
    using ImplementationType = HminImplementation<ImageType, ImageType>;

protected:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        PixelType featureHeight = getFeatureHeight();

        return ImplementationType(featureHeight, sourceImage, destinationImage);
    }

    virtual PixelType getFeatureHeight() = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = HminTestData<HminImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
