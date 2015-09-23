#ifndef INVERSION_IMPLEMENTATION_TEST_HPP
#define INVERSION_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionImplementation.hpp"

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
using TestData = InversionTestData<PixelType, ImageType>;

#endif
