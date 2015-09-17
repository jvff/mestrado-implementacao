#ifndef IMAGE_IMPLEMENTATION_TEST_HPP
#define IMAGE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "Image.hpp"

template <typename ImageType, typename PixelType>
class ImageImplementationTest : public ::testing::Test {
protected:
    void testSinglePixel(PixelType value) {
        testPixelsWithSameValue(1, 1, value);
    }

    void testPixelsWithSameValue(unsigned int width, unsigned int height,
            PixelType value) {
        ImageType image(width, height);

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                image.setPixel(x, y, value);
        }

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                comparePixel(image.getPixel(x, y), value);
        }
    }

    void testPixels(unsigned int width, unsigned int height,
            const PixelType values[]) {
        ImageType image(width, height);
        const PixelType* pixelIterator = &values[0];

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                image.setPixel(x, y, *(pixelIterator++));
        }

        pixelIterator = &values[0];

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                comparePixel(x, y, *(pixelIterator++), image.getPixel(x, y));
        }
    }

    virtual void comparePixel(unsigned int x, unsigned int y,
            PixelType expected, PixelType actual) {
        if (comparePixel(expected, actual) == false) {
            FAIL() << "Pixel at (" << x << "," << y << ")" << std::endl
                    << "Expected: " << expected << std::endl
                    << "  Actual: " << actual;
        }
    }

    virtual bool comparePixel(PixelType expected, PixelType actual) {
        return expected == actual;
    }
};

#endif
