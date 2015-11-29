#ifndef MAX_TREE_IMPLEMENTATION_TEST_HPP
#define MAX_TREE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MaxTreeImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using DummyImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
};

#endif
