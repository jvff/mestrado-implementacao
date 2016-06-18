#ifndef LUMINANCE_FILTER_RGB_IMAGE_IMPLEMENTATION_TEST_HPP
#define LUMINANCE_FILTER_RGB_IMAGE_IMPLEMENTATION_TEST_HPP

#include "LuminanceFilterImplementationTests.hpp"

#include "../TestImageFactory.hpp"

template <typename Aliases>
class LuminanceFilterRgbImageImplementationTest : public ::testing::Test {
private:
    using SourceImageType = typename Aliases::SourceImageType;
    using InternalImageType = typename SourceImageType::InternalImageType;
    using DestinationImageType = typename Aliases::DestinationImageType;

    template <class ImageType>
    using ImageFactoryPointer = std::shared_ptr<TestImageFactory<ImageType> >;

protected:
    using DestinationPixelType = typename DestinationImageType::PixelType;

private:
    static ImageFactoryPointer<InternalImageType> internalImageFactory;
    static ImageFactoryPointer<DestinationImageType> destinationImageFactory;

public:
    static void SetUpTestCase() {
        internalImageFactory.reset(new TestImageFactory<InternalImageType>());
        destinationImageFactory.reset(
                new TestImageFactory<DestinationImageType>());
    }

    static void TearDownTestCase() {
        internalImageFactory.reset();
        destinationImageFactory.reset();
    }

protected:
    InternalImageType createInternalImage(unsigned int width,
            unsigned int height) {
        return internalImageFactory->createImage(width, height);
    }

    DestinationImageType createDestinationImage(unsigned int width,
            unsigned int height) {
        return destinationImageFactory->createImage(width, height);
    }

    DestinationPixelType convertFloatDestinationValue(float value) {
        auto saturatedValue = std::numeric_limits<DestinationPixelType>::max();
        int numberOfRepresentableBits = sizeof(DestinationPixelType) * 8;

        if (std::numeric_limits<DestinationPixelType>::is_signed) {
            numberOfRepresentableBits -= 1;

            if (value < 0.f)
                saturatedValue -= 1;
        } else if (value < 0.f)
            return 0;

        int exponent;

        std::frexp(value, &exponent);

        if (exponent > numberOfRepresentableBits)
            return saturatedValue;
        else
            return (DestinationPixelType)value;
    }
};

template <typename Aliases>
std::shared_ptr<TestImageFactory<
                typename LuminanceFilterRgbImageImplementationTest<Aliases>
                        ::InternalImageType> >
        LuminanceFilterRgbImageImplementationTest<Aliases>
                ::internalImageFactory;

template <typename Aliases>
std::shared_ptr<TestImageFactory<
                typename LuminanceFilterRgbImageImplementationTest<Aliases>
                        ::DestinationImageType> >
        LuminanceFilterRgbImageImplementationTest<Aliases>
                ::destinationImageFactory;

#define TEST_C(testName) \
    TEST_C_FOR_TEST_CASE(LuminanceFilterRgbImageImplementationTest, testName, \
        using SuperClass::createInternalImage; \
        using SuperClass::createDestinationImage; \
        using SuperClass::convertFloatDestinationValue; \
    )

#endif
