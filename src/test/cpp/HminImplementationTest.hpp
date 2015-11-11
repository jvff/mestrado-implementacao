#ifndef HMIN_IMPLEMENTATION_TEST_HPP
#define HMIN_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class HminImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = HminImplementation<SourceImageType,
            DestinationImageType>;
};

#endif
