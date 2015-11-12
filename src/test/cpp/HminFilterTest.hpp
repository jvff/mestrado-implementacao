#ifndef HMIN_FILTER_TEST_HPP
#define HMIN_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "HminFilter.hpp"
#include "HminImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class HminFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HminFilter<SourceImageType, DestinationImageType>;
};

#endif
