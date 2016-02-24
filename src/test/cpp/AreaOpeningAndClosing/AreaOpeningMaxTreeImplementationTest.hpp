#ifndef AREA_OPENING_MAX_TREE_IMPLEMENTATION_TEST_HPP
#define AREA_OPENING_MAX_TREE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "FilterImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "../AbstractFilterImplementationTestData.hpp"
#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#include "AreaOpeningAndClosingTestData.hpp"

class AreaOpeningMaxTreeImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningMaxTreeImplementation<
            SourceImageType, DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaOpeningMaxTreeImplementationTestData
        : public AbstractFilterImplementationTestData<
                AreaOpeningMaxTreeImplementation<ImageType, ImageType>,
                ImageType, ImageType> {
private:
    using ImplementationType = AreaOpeningMaxTreeImplementation<ImageType,
            ImageType>;

protected:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        return ImplementationType(getMaximumExtremitySize(), sourceImage,
                destinationImage);
    }

    virtual unsigned int getMaximumExtremitySize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningAndClosingTestData<
        AbstractAreaOpeningMaxTreeImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
