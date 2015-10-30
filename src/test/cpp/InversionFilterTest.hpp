#ifndef INVERSION_FILTER_TEST_HPP
#define INVERSION_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionFilter.hpp"
#include "InversionImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "InversionTestData.hpp"

class InversionFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using DummyFilterType = InversionFilter<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractInversionFilterTestData : public AbstractFilterTestData<
        InversionFilter<ImageType, ImageType>, ImageType,
        ImageType> {
private:
    using SuperClass = AbstractFilterTestData<
            InversionFilter<ImageType, ImageType>, ImageType, ImageType>;

protected:
    void runTest() {
        if (shouldUseManualRange())
            SuperClass::initializeFilter(getMinimumValue(), getMaximumValue());
        else
            SuperClass::initializeFilter();

        SuperClass::runTest();
    }

    virtual bool shouldUseManualRange() = 0;
    virtual PixelType getMinimumValue() = 0;
    virtual PixelType getMaximumValue() = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = InversionTestData<
        AbstractInversionFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
