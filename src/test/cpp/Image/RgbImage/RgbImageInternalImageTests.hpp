#ifndef RGB_IMAGE_INTERNAL_IMAGE_TESTS_HPP
#define RGB_IMAGE_INTERNAL_IMAGE_TESTS_HPP

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "AbstractRgbImageTestWithInternalImageMock.hpp"

#include "../../CustomTypedTestMacros.hpp"

using namespace fakeit;

template <typename PixelType>
class RgbImageInternalImageTests
        : public AbstractRgbImageTestWithInternalImageMock<PixelType> {
protected:
    using SuperClass = AbstractRgbImageTestWithInternalImageMock<PixelType>;
    using InternalImageType = typename SuperClass::InternalImageType;
    using PaintFunction = typename SuperClass::PaintFunction;

protected:
    Mock<InternalImageType> mockSimpleInternalImage(unsigned int width,
            unsigned int height) {
        auto paintFunction = [=] (unsigned int x, unsigned int y) -> PixelType {
            return x + y * width;
        };

        return mockInternalImage(width, height, paintFunction);
    }

private:
    using SuperClass::mockInternalImage;
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
