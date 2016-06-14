#ifndef RGB_IMAGE_INTERNAL_IMAGE_TESTS_HPP
#define RGB_IMAGE_INTERNAL_IMAGE_TESTS_HPP

#include <functional>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "../../CustomTypedTestMacros.hpp"
#include "../../FakeImage.hpp"

using namespace fakeit;

template <typename PixelType>
class RgbImageInternalImageTests : public ::testing::Test {
protected:
    using InternalImageType = FakeImage<PixelType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

protected:
    Mock<InternalImageType> mockSimpleInternalImage(unsigned int width,
            unsigned int height) {
        return mockInternalImage(width, height, getSimplePaintFunction(width));
    }

private:
    Mock<InternalImageType> mockInternalImage(unsigned int width,
            unsigned int height, PaintFunction paintFunction) {
        Mock<InternalImageType> mockImage;

        auto returnPixel = paintFunction;

        When(Method(mockImage, getWidth)).AlwaysReturn(width);
        When(Method(mockImage, getHeight)).AlwaysReturn(height);
        When(Method(mockImage, getPixelValue)).AlwaysDo(returnPixel);
        When(Method(mockImage, setPixel).Using(Lt(width), Lt(height), _))
            .AlwaysReturn();

        return mockImage;
    }

    PaintFunction getSimplePaintFunction(unsigned int width) {
        return [width] (unsigned int x, unsigned int y) -> PixelType {
            return x + y * width;
        };
    }
};

#define TEST_C(TestName) \
    CREATE_RGB_IMAGE_INTERNAL_IMAGE_TESTS_CLASS(TestName); \
    REGISTER_CUSTOM_TYPED_TEST(RgbImageInternalImageTests, TestName); \
    START_CUSTOM_TYPED_TEST_BODY(RgbImageInternalImageTests, TestName)

#define CREATE_RGB_IMAGE_INTERNAL_IMAGE_TESTS_CLASS(TestName) \
template <typename PixelTypeParameter> \
class GTEST_TEST_CLASS_NAME_(RgbImageInternalImageTests, TestName) \
        : public RgbImageInternalImageTests<PixelTypeParameter> { \
private: \
    using PixelType = PixelTypeParameter; \
    using SuperClass = RgbImageInternalImageTests<PixelType>; \
    using InternalImageType = typename SuperClass::InternalImageType; \
    using RgbImageType = RgbImage<InternalImageType>; \
\
public: \
    void TestBody(); \
\
private: \
    using SuperClass::mockSimpleInternalImage; \
}

#endif
