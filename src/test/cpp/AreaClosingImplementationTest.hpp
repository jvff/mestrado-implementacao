#ifndef AREA_CLOSING_IMPLEMENTATION_TEST_HPP
#define AREA_CLOSING_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingImplementation.hpp"

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

#endif
