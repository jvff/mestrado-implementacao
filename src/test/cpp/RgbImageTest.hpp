#ifndef RGB_IMAGE_TEST_HPP
#define RGB_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "FakeImage.hpp"

using namespace fakeit;

class RgbImageTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageType = RgbImage<InternalImageType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

protected:
    Mock<InternalImageType> mockInternalImage(unsigned int width,
            unsigned int height) {
        Mock<InternalImageType> mockImage;

        auto returnPixel = getPaintFunction(width);

        When(Method(mockImage, getWidth)).AlwaysReturn(width);
        When(Method(mockImage, getHeight)).AlwaysReturn(height);
        When(Method(mockImage, getPixelValue)).AlwaysDo(returnPixel);
        When(Method(mockImage, setPixel).Using(Lt(width), Lt(height), _))
            .AlwaysReturn();

        return mockImage;
    }

    PaintFunction getPaintFunction(unsigned int width) {
        return [width] (unsigned int x, unsigned int y) -> PixelType {
            return x + y * width;
        };
    }
};

#endif
