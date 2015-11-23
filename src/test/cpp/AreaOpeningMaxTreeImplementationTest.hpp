#ifndef AREA_OPENING_MAX_TREE_IMPLEMENTATION_TEST_HPP
#define AREA_OPENING_MAX_TREE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "FilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class AreaOpeningMaxTreeImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningMaxTreeImplementation<
            SourceImageType, DestinationImageType>;
};

#endif
