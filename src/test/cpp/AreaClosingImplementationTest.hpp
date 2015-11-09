#ifndef AREA_CLOSING_IMPLEMENTATION_TEST_HPP
#define AREA_CLOSING_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingImplementation.hpp"
#include "FilterImplementation.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "AreaOpeningAndClosingTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class AreaClosingImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaClosingImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaClosingImplementationTestData
        : public AbstractFilterImplementationTestData<AreaClosingImplementation<
                ImageType, ImageType>, ImageType, ImageType> {
private:
    using ImplementationType = AreaClosingImplementation<ImageType, ImageType>;

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
        AbstractAreaClosingImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
