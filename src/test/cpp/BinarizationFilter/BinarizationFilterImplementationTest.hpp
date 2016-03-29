#ifndef BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP
#define BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP

#include "BinarizationFilterTest.hpp"

#include "../CustomTypedTestMacros.hpp"

template <typename Aliases>
class BinarizationFilterImplementationTest : public ::testing::Test {
};

template <typename SourceImageTypeParameter,
        typename RealSourceImageTypeParameter,
        typename DestinationImageTypeParameter>
struct AliasesWithoutComparator {
    using SourceImageType = SourceImageTypeParameter;
    using RealSourceImageType = RealSourceImageTypeParameter;
    using DestinationImageType = DestinationImageTypeParameter;

    using PixelType = typename SourceImageType::PixelType;
    using FilterType = BinarizationFilter<SourceImageType,
            DestinationImageType>;
    using TestImageType = TestImage<PixelType>;
};

template <typename SourceImageTypeParameter,
        typename RealSourceImageTypeParameter,
        typename DestinationImageTypeParameter,
        template <typename> class ComparatorTemplate>
struct AliasesWithComparator {
    using SourceImageType = SourceImageTypeParameter;
    using RealSourceImageType = RealSourceImageTypeParameter;
    using DestinationImageType = DestinationImageTypeParameter;

    using PixelType = typename SourceImageType::PixelType;
    using FilterType = BinarizationFilter<SourceImageType,
            DestinationImageType, ComparatorTemplate>;
    using TestImageType = TestImage<PixelType, ComparatorTemplate>;
};

#undef TEST_C
#define TEST_C(testName) \
    CREATE_BINARIZATION_FILTER_IMPLEMENTATION_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(BinarizationFilterImplementationTest, \
            testName); \
    START_CUSTOM_TYPED_TEST_BODY(BinarizationFilterImplementationTest, testName)

#define CREATE_BINARIZATION_FILTER_IMPLEMENTATION_TEST_CLASS(testName) \
template <typename Aliases> \
class GTEST_TEST_CLASS_NAME_(BinarizationFilterImplementationTest, testName) \
        : public BinarizationFilterImplementationTest<Aliases> { \
private: \
    using SourceImageType = typename Aliases::SourceImageType; \
    using RealSourceImageType = typename Aliases::RealSourceImageType; \
\
    using FilterType = typename Aliases::FilterType; \
    using TestImageType = typename Aliases::TestImageType; \
\
private: \
    virtual void TestBody(); \
}

#endif
