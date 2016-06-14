#ifndef ABSTRACT_RGB_IMAGE_TEST_WITH_INTERNAL_IMAGE_MOCK_HPP
#define ABSTRACT_RGB_IMAGE_TEST_WITH_INTERNAL_IMAGE_MOCK_HPP

#include <functional>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "../../FakeImage.hpp"

using namespace fakeit;

template <typename PixelType>
class AbstractRgbImageTestWithInternalImageMock : public ::testing::Test {
protected:
    using InternalImageType = FakeImage<PixelType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

protected:
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
};

#endif
