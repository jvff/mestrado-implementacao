#ifndef LUMINANCE_FILTER_IMPLEMENTATION_TESTS_HPP
#define LUMINANCE_FILTER_IMPLEMENTATION_TESTS_HPP

#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "Filter.hpp"
#include "LuminanceFilter.hpp"
#include "OpenCLImage.hpp"
#include "RgbImage.hpp"
#include "SimpleArrayImage.hpp"
#include "SimpleFilter.hpp"

#include "../CustomTypedTestMacros.hpp"
#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

using namespace fakeit;

template <typename SourceImageTypeParameter,
        typename RealSourceImageTypeParameter,
        typename DestinationImageTypeParameter>
struct Aliases {
    using SourceImageType = SourceImageTypeParameter;
    using RealSourceImageType = RealSourceImageTypeParameter;
    using DestinationImageType = DestinationImageTypeParameter;

    using FilterType = LuminanceFilter<SourceImageType, DestinationImageType>;
};

#define TEST_C_FOR_TEST_CASE(testCase, testName, extraCode) \
    CREATE_LUMINANCE_FILTER_IMPLEMENTATION_TEST_CLASS(testCase, testName, \
            extraCode); \
    REGISTER_CUSTOM_TYPED_TEST(testCase, testName); \
    START_CUSTOM_TYPED_TEST_BODY(testCase, testName)

#define CREATE_LUMINANCE_FILTER_IMPLEMENTATION_TEST_CLASS(testCase, testName, \
        extraCode) \
template <typename Aliases> \
class GTEST_TEST_CLASS_NAME_(testCase, testName) : public testCase<Aliases> { \
private: \
    using SuperClass = testCase<Aliases>; \
\
    using SourceImageType = typename Aliases::SourceImageType; \
    using RealSourceImageType = typename Aliases::RealSourceImageType; \
    using DestinationImageType = typename Aliases::DestinationImageType; \
\
    using FilterType = typename Aliases::FilterType; \
\
private: \
    extraCode \
\
private: \
    virtual void TestBody(); \
}

#endif
