#ifndef BASIC_TESTS_HPP
#define BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "FilterImplementation.hpp"

#include "../../DummyTypes.hpp"
#include "../../FakeImage.hpp"

class AreaOpeningAndClosingMinMaxTreeImplementationTest
        : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningMaxTreeImplementation<
            SourceImageType, DestinationImageType>;
};

#define TEST_C(testName) \
        TEST_F(AreaOpeningAndClosingMinMaxTreeImplementationTest, testName)

#endif
