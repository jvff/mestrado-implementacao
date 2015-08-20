#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using namespace fakeit;

class ImageTest : public testing::Test {
protected:
    using DummyImage = Image<DummyType>;
    using FakeDummyImage = FakeImage<DummyType>;
    using PaintFunction = std::function<DummyType(unsigned int, unsigned int)>;

    Mock<FakeDummyImage> spyImage(FakeDummyImage& image) {
        Mock<FakeDummyImage> spy(image);

        Spy(Method(spy, setPixel));
        Spy(Method(spy, getPixel));

        return spy;
    }

    Mock<FakeDummyImage> createMockImage(unsigned int width,
            unsigned int height) {
        Mock<FakeDummyImage> mock;

        auto returnPixel = getPaintFunction(width);

        When(Method(mock, getWidth)).AlwaysReturn(width);
        When(Method(mock, getHeight)).AlwaysReturn(height);
        When(Method(mock, getPixel)).AlwaysDo(returnPixel);

        return mock;
    }

    void interceptPixel(Mock<FakeDummyImage>& mock, unsigned int x,
            unsigned int y, DummyType pixelValue) {
        When(Method(mock, getPixel).Using(x, y)).Return(pixelValue);
    }

    void verifyImageWasPainted(Mock<FakeDummyImage>& mock) {
        auto image = mock.get();
        auto width = image.getWidth();
        auto height = image.getHeight();

        DummyType pixelValue = {0};

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                Verify(Method(mock, setPixel).Using(x, y, pixelValue));

                ++pixelValue.value;
            }
        }

        VerifyNoOtherInvocations(Method(mock, setPixel));
    }

    static PaintFunction getPaintFunction(unsigned int width) {
        return [width] (unsigned int x, unsigned int y) {
            return DummyType{ (int)(y * width + x) };
        };
    }
};

#endif
