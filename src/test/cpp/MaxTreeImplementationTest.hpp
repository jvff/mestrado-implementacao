#ifndef MAX_TREE_IMPLEMENTATION_TEST_HPP
#define MAX_TREE_IMPLEMENTATION_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "MaxTreeTestData.hpp"

template <typename TypeParameter>
class MaxTreeImplementationTest : public ::testing::Test {
protected:
    template <typename T>
    using TreeTypeComparator =
            typename TypeParameter::template ComparatorFor<T>;

    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using LevelOrderComparator = TreeTypeComparator<DestinationPixelType>;
    using DestinationImageType = MinMaxTreeImage<InternalImageType,
            LevelOrderComparator>;
    using DummyImplementationType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, TreeTypeComparator>;
};

template <template <typename> class Comparator>
struct ComparatorWrapper {
    template <typename T>
    using ComparatorFor = Comparator<T>;
};

#define TEST_C(testName) \
    CREATE_MAX_TREE_IMPLEMENTATION_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeImplementationTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeImplementationTest, testName)

#define CREATE_MAX_TREE_IMPLEMENTATION_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeImplementationTest, testName) \
        : public MaxTreeImplementationTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeImplementationTest<TypeParameter>; \
    using SourceImageType = typename SuperClass::SourceImageType; \
    using DestinationImageType = typename SuperClass::DestinationImageType; \
    using DummyImplementationType = \
            typename SuperClass::DummyImplementationType; \
\
private: \
    virtual void TestBody(); \
}

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MaxTreeTestData<AbstractFilterImplementationTestData<
            MaxTreeImplementation<ImageType, ImageType>,
            ImageType, MaxTreeImage<ImageType> >,
        PixelType, ImageType>;

#endif
