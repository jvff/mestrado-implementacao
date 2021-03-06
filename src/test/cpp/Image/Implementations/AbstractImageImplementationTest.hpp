#ifndef ABSTRACT_IMAGE_IMPLEMENTATION_TEST_HPP
#define ABSTRACT_IMAGE_IMPLEMENTATION_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"

#include "../../AbstractTestWithImage.hpp"

template <typename ImageType, typename PixelType>
class AbstractImageImplementationTest
        : public AbstractTestWithImage<ImageType> {
protected:
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;
    using SuperClass = AbstractTestWithImage<ImageType>;

protected:
    void testSinglePixel(PixelType value) {
        testPixelsWithSameValue(1, 1, value);
    }

    void testPixelsWithSameValue(unsigned int width, unsigned int height,
            PixelType value) {
        auto image = createImage(width, height);

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                setPixel(image, x, y, value);
        }

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                comparePixel(x, y, value, getPixel(image, x, y));
        }
    }

    void testPixels(unsigned int width, unsigned int height,
            const PixelType values[]) {
        auto image = createImage(width, height);
        const PixelType* pixelIterator = &values[0];

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                setPixel(image, x, y, *(pixelIterator++));
        }

        pixelIterator = &values[0];

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                comparePixel(x, y, *(pixelIterator++), getPixel(image, x, y));
        }
    }

    void testPixelsUsingLambda(unsigned int width, unsigned int height,
            PaintFunction values) {
        auto image = createImage(width, height);

        image = values;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                comparePixel(x, y, values(x, y), getPixel(image, x, y));
        }
    }

    virtual void comparePixel(unsigned int x, unsigned int y,
            PixelType expected, PixelType actual) {
        if (comparePixelValues(expected, actual) == false) {
            FAIL() << "Pixel at (" << x << "," << y << ")" << std::endl
                    << "Expected: " << expected << std::endl
                    << "  Actual: " << actual;
        }
    }

    virtual bool comparePixelValues(PixelType expected, PixelType actual) {
        return expected == actual;
    }

    PixelType getPixel(const ImageType& image, unsigned int x, unsigned int y) {
        auto pixel = getPixelObject(image, x, y);
        auto value = getPixelValue(image, x, y);

        assertThat(pixel.x).isEqualTo(x);
        assertThat(pixel.y).isEqualTo(y);
        assertThat(pixel.value).isEqualTo(value);

        return value;
    }

    virtual Pixel<PixelType> getPixelObject(const ImageType& image,
            unsigned int x, unsigned int y) = 0;
    virtual PixelType getPixelValue(const ImageType& image, unsigned int x,
            unsigned int y) = 0;
    virtual void setPixel(ImageType& image, unsigned int x, unsigned int y,
            const PixelType& value) = 0;

    using SuperClass::createImage;
};

#endif
