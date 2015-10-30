#ifndef INVERSION_FILTER_TEST_HPP
#define INVERSION_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionFilter.hpp"
#include "InversionImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class InversionFilterTest : public ::testing::Test {
protected:
    using SourceImageType = Image<DummyTypes<1> >;
    using DestinationImageType = FakeImage<DummyTypes<2> >;
    using ImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using DummyFilterType = InversionFilter<SourceImageType,
            DestinationImageType>;
};

#endif
