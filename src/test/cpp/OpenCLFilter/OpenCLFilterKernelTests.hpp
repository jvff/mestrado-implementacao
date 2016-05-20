#ifndef OPEN_C_L_FILTER_KERNEL_TESTS_HPP
#define OPEN_C_L_FILTER_KERNEL_TESTS_HPP

#include <functional>
#include <string>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

#include "../AssertionsSpecificForCLNDRange.hpp"
#include "../AbstractOpenCLTest.hpp"

#include "FakeOpenCLFilter.hpp"
#include "OpenCLFilterOnImageQuarters.hpp"
#include "OpenCLFilterOnQuarterImage.hpp"

#include "../cl/OpenCLFilterTestKernels.h"

class OpenCLFilterKernelTests : public AbstractOpenCLTest {
protected:
    using SuperClass = AbstractOpenCLTest;

    using PixelType = unsigned int;
    using ImageType = OpenCLImage<PixelType>;
    using FilterType = OpenCLFilter<PixelType>;

    using ImageFunction = std::function<PixelType(unsigned int, unsigned int)>;

protected:
    static std::string kernelSourceCode;

protected:
    static void SetUpTestCase() {
        SuperClass::SetUpTestCase();

        kernelSourceCode = OpenCLFilterTestKernelsSourceCode;
    }

    static PixelType coordinateSumPixels(unsigned int x, unsigned int y) {
        return x + y;
    }

    static PixelType zeroedPixels(unsigned int, unsigned int) {
        return 0;
    }

protected:
    ImageFunction pixelsInOrder(unsigned int width) {
        return [=] (unsigned int x, unsigned int y) {
            return x + y * width;
        };
    }

    ImageFunction pixelsInQuartetInOrder(unsigned int width,
            unsigned int height) {
        auto halfWidth = width / 2;
        auto halfHeight = height / 2;

        return [=] (unsigned int x, unsigned int y) {
            auto xInQuarter = x % halfWidth;
            auto yInQuarter = y % halfHeight;

            return xInQuarter + yInQuarter * width;
        };
    }

    void verifyImagePixels(const ImageType& image,
            ImageFunction expectedPixels) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        verifyImagePixels(image, width, height, expectedPixels);
    }

    void verifyImagePixels(const ImageType& image, unsigned int width,
            unsigned int height, ImageFunction expectedPixels) {
        verifyImagePixels(image, 0u, 0u, width, height, expectedPixels);
    }

    void verifyImagePixels(const ImageType& image, unsigned int startX,
            unsigned int startY, unsigned int endX, unsigned int endY,
            ImageFunction expectedPixels) {
        for (auto x = startX; x < endX; ++x) {
            for (auto y = startY; y < endY; ++y) {
                auto pixelValue = image.getPixelValue(x, y);
                auto expectedPixelValue = expectedPixels(x, y);

                assertThat(pixelValue).isEqualTo(expectedPixelValue);
            }
        }
    }
};

#define TEST_C(TestName) \
    TEST_F(OpenCLFilterKernelTests, TestName)

#endif
