#ifndef BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP
#define BINARIZATION_FILTER_IMPLEMENTATION_TEST_HPP

#include <functional>
#include <memory>
#include <type_traits>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "OpenCLImage.hpp"
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

    template <typename ReturnType, bool Condition>
    using FunctionSpecialization =
            typename std::enable_if<Condition, ReturnType>::type;

    template <typename ImageType, typename... ConstructorParameters>
    using SpecializationForImageType = FunctionSpecialization<
            std::shared_ptr<ImageType>,
            std::is_constructible<ImageType, ConstructorParameters...>::value>;

    template <typename ImageType>
    using SpecializationForSimpleImage = SpecializationForImageType<ImageType,
            unsigned int, unsigned int>;

    template <typename ImageType>
    using SpecializationForOpenCLImage = SpecializationForImageType<ImageType,
            unsigned int, unsigned int, cl::Context&, cl::CommandQueue&>;

protected:
    static cl::Context context;
    static cl::CommandQueue commandQueue;

public:
    static void SetUpTestCase() {
        auto defaultDevice = cl::Device::getDefault();

        context = cl::Context::getDefault();
        commandQueue = cl::CommandQueue(context, defaultDevice);
    }

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
        paintExpectedImage<DestinationImageType>();
    }

    template <typename ImageType>
    SpecializationForSimpleImage<ImageType> makeImage(unsigned int width,
            unsigned int height) {
        return std::make_shared<ImageType>(width, height);
    }

    template <typename ImageType>
    SpecializationForOpenCLImage<ImageType> makeImage(unsigned int width,
            unsigned int height) {
        return std::make_shared<ImageType>(width, height, context,
                commandQueue);
    }

private:
    void paintSourceImage() {
        *sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
            return (PixelType)x - (PixelType)y;
        };
    }

    template <typename ImageType>
    SpecializationForSimpleImage<ImageType> paintExpectedImage() {
        *expectedImage = [&] (unsigned int x, unsigned int y) -> bool {
            auto pixelValue = (PixelType)x - (PixelType)y;

            return comparator(pixelValue, threshold);
        };

        return expectedImage;
    }

    template <typename ImageType>
    SpecializationForOpenCLImage<ImageType> paintExpectedImage() {
        auto trueValue = 0xFFFFFFFFu;
        auto falseValue = 0;

        *expectedImage = [trueValue, falseValue, this] (unsigned int x,
                unsigned int y) -> PixelType {
            auto pixelValue = (PixelType)x - (PixelType)y;

            if (comparator(pixelValue, threshold))
                return trueValue;
            else
                return falseValue;
        };

        return expectedImage;
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
    template <typename ImageType> \
    std::shared_ptr<ImageType> makeImage(unsigned int width, unsigned int height) { \
        return SuperClass::template makeImage<ImageType>(width, height); \
    } \
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
