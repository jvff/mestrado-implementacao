#ifndef RGB_IMAGE_COLOR_CHANNEL_TESTS_HPP
#define RGB_IMAGE_COLOR_CHANNEL_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "AbstractRgbImageTestWithColorChannels.hpp"

#include "../../CustomTypedTestMacros.hpp"

template <typename PixelType>
class RgbImageColorChannelTests
        : public AbstractRgbImageTestWithColorChannels<PixelType> {
protected:
    using SuperClass = AbstractRgbImageTestWithColorChannels<PixelType>;
    using InternalImageType = typename SuperClass::InternalImageType;
    using PaintFunction = typename SuperClass::PaintFunction;
    using RgbImageType = typename SuperClass::RgbImageType;

protected:
    using SuperClass::checkChannelsOfAllPixels;
    using SuperClass::checkRelativeChannelsOfAllPixels;
    using SuperClass::initializePainter;
    using SuperClass::mockColorInternalImage;
};

#define TEST_C(TestName) \
    CREATE_RGB_IMAGE_COLOR_CHANNEL_TESTS_CLASS(TestName); \
    REGISTER_CUSTOM_TYPED_TEST(RgbImageColorChannelTests, TestName); \
    START_CUSTOM_TYPED_TEST_BODY(RgbImageColorChannelTests, TestName)

#define CREATE_RGB_IMAGE_COLOR_CHANNEL_TESTS_CLASS(TestName) \
template <typename PixelTypeParameter> \
class GTEST_TEST_CLASS_NAME_(RgbImageColorChannelTests, TestName) \
        : public RgbImageColorChannelTests<PixelTypeParameter> { \
private: \
    using PixelType = PixelTypeParameter; \
    using SuperClass = RgbImageColorChannelTests<PixelType>; \
    using InternalImageType = typename SuperClass::InternalImageType; \
    using RgbImageType = typename SuperClass::RgbImageType; \
\
public: \
    void TestBody(); \
\
private: \
    using SuperClass::checkChannelsOfAllPixels; \
    using SuperClass::checkRelativeChannelsOfAllPixels; \
    using SuperClass::initializePainter; \
    using SuperClass::mockColorInternalImage; \
}

#endif
