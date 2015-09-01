#ifndef AREA_OPENING_IMPLEMENTATION_TEST_HPP
#define AREA_OPENING_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningImplementation.hpp"
#include "SimpleArrayImage.hpp"

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

#endif
