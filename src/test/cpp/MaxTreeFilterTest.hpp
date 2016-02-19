#ifndef MAX_TREE_FILTER_TEST_HPP
#define MAX_TREE_FILTER_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

#include "AbstractFilterTestData.hpp"
#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "MinMaxTreeTestData.hpp"

template <typename TypeParameter>
class MaxTreeFilterTest : public ::testing::Test {
protected:
    template <typename T>
    using TreeTypeComparator =
            typename TypeParameter::template ComparatorFor<T>;

    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DummyMaxTreeFilter = MinMaxTreeFilter<SourceImageType,
            InternalImageType, TreeTypeComparator>;
};

template <template <typename> class Comparator>
struct ComparatorWrapper {
    template <typename T>
    using ComparatorFor = Comparator<T>;
};

#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_FILTER_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeFilterTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeFilterTest, testName)

#define CREATE_MIN_MAX_TREE_FILTER_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeFilterTest, testName) \
        : public MaxTreeFilterTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeFilterTest<TypeParameter>; \
    using SourceImageType = typename SuperClass::SourceImageType; \
    using InternalImageType = typename SuperClass::InternalImageType; \
    using DummyMaxTreeFilter = typename SuperClass::DummyMaxTreeFilter; \
\
private: \
    virtual void TestBody(); \
}

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractMaxTreeFilterTestData : public AbstractFilterTestData<
        MaxTreeFilter<ImageType, ImageType>, ImageType,
        MaxTreeImage<ImageType> > {
public:
    AbstractMaxTreeFilterTestData() {
        this->initializeFilter();
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MinMaxTreeTestData<AbstractMaxTreeFilterTestData<PixelType,
            ImageType>, std::less, PixelType, ImageType>;

#endif
