#ifndef MAX_TREE_FILTER_TEST_HPP
#define MAX_TREE_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MaxTreeFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DummyMaxTreeFilter = MaxTreeFilter<SourceImageType,
            InternalImageType>;
};

#endif
