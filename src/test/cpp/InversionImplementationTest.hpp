#ifndef INVERSION_IMPLEMENTATION_TEST_HPP
#define INVERSION_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "InversionTestData.hpp"

class InversionImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = InversionImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractInversionImplementationTestData
        : public AbstractFilterImplementationTestData<
                InversionImplementation<ImageType, ImageType>, ImageType,
                ImageType> {
private:
    using ImplementationType = InversionImplementation<ImageType, ImageType>;

public:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        if (shouldUseManualRange()) {
            return ImplementationType(sourceImage, destinationImage,
                    getMinimumValue(), getMaximumValue());
        } else
            return ImplementationType(sourceImage, destinationImage);
    }

protected:
    virtual bool shouldUseManualRange() = 0;
    virtual PixelType getMinimumValue() = 0;
    virtual PixelType getMaximumValue() = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = InversionTestData<
        AbstractInversionImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
