#ifndef AREA_OPENING_IMPLEMENTATION_TEST_HPP
#define AREA_OPENING_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "AreaOpeningTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class AreaOpeningImplementationTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaOpeningImplementationTestData
        : public AbstractFilterImplementationTestData<AreaOpeningImplementation<
                ImageType, ImageType>, ImageType, ImageType> {
private:
    using ImplementationType = AreaOpeningImplementation<ImageType, ImageType>;

protected:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        return ImplementationType(getMaximumPeakSize(), sourceImage,
                destinationImage);
    }

    virtual unsigned int getMaximumPeakSize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningTestData<
        AbstractAreaOpeningImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
