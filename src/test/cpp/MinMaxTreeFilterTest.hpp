#ifndef MIN_MAX_TREE_FILTER_TEST_HPP
#define MIN_MAX_TREE_FILTER_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "MinMaxTreeFilter.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeImplementation.hpp"

#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename TypeParameter>
class MinMaxTreeFilterTest : public ::testing::Test {
};

template <template <typename> class TreeTypeComparator>
struct MinMaxTreeFilterTestAliases {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using LevelOrderComparator = TreeTypeComparator<DestinationPixelType>;
    using DestinationImageType = MinMaxTreeImage<InternalImageType,
            LevelOrderComparator>;
    using DummyMinMaxTreeFilter = MinMaxTreeFilter<SourceImageType,
            InternalImageType, TreeTypeComparator>;
    using ImplementationType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, TreeTypeComparator>;
};

#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_FILTER_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeFilterTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeFilterTest, testName)

#define CREATE_MIN_MAX_TREE_FILTER_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeFilterTest, testName) \
        : public MinMaxTreeFilterTest<TypeParameter> { \
private: \
    using SourceImageType = typename TypeParameter::SourceImageType; \
    using InternalImageType = typename TypeParameter::InternalImageType; \
    using DestinationImageType = typename TypeParameter::DestinationImageType; \
    using DummyMinMaxTreeFilter = \
            typename TypeParameter::DummyMinMaxTreeFilter; \
    using ImplementationType = typename TypeParameter::ImplementationType; \
\
private: \
    virtual void TestBody(); \
}

#endif
