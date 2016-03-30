#ifndef BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP
#define BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP

#include <functional>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "../CustomTypedTestMacros.hpp"

#include "EqualsComparator.hpp"

template <typename Aliases>
class BinarizationFilterImplementationTest : public ::testing::Test {
private:
    using Comparator = typename Aliases::Comparator;
    using DestinationImageType = typename Aliases::DestinationImageType;
    using FilterType = typename Aliases::FilterType;
    using PixelType = typename Aliases::PixelType;
    using RealSourceImageType = typename Aliases::RealSourceImageType;
    using SourceImageType = typename Aliases::SourceImageType;

protected:
    Comparator comparator;
    PixelType threshold;

    std::shared_ptr<FilterType> filter;
    std::shared_ptr<SourceImageType> sourceImage;
    std::shared_ptr<DestinationImageType> expectedImage;

protected:
    void initialize(unsigned int width, unsigned int height,
            const PixelType& threshold) {
        this->threshold = threshold;

        filter = std::make_shared<FilterType>(threshold);

        sourceImage = makeImage<RealSourceImageType>(width, height);
        expectedImage = makeImage<DestinationImageType>(width, height);

        paintSourceImage();
        paintExpectedImage();
    }

private:
    template <typename ImageType>
    std::shared_ptr<ImageType> makeImage(unsigned int width,
            unsigned int height) {
        return std::make_shared<ImageType>(width, height);
    }

    void paintSourceImage() {
        *sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
            return (PixelType)x - (PixelType)y;
        };
    }

    void paintExpectedImage() {
        *expectedImage = [&] (unsigned int x, unsigned int y) -> bool {
            auto pixelValue = (PixelType)x - (PixelType)y;

            return comparator(pixelValue, threshold);
        };
    }
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

    using Comparator = std::greater<PixelType>;
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

    using Comparator = ComparatorTemplate<PixelType>;
};

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
    using SuperClass = BinarizationFilterImplementationTest<Aliases>; \
\
    using SourceImageType = typename Aliases::SourceImageType; \
    using RealSourceImageType = typename Aliases::RealSourceImageType; \
\
    using FilterType = typename Aliases::FilterType; \
\
private: \
    using SuperClass::initialize; \
\
private: \
    using SuperClass::filter; \
    using SuperClass::sourceImage; \
    using SuperClass::expectedImage; \
\
private: \
    virtual void TestBody(); \
}

#endif
