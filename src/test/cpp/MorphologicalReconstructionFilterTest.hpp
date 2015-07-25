#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class TestData {
private:
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using Pixel = std::tuple<unsigned int, unsigned int, const PixelType&>;

public:
    FilterType filter;
    ImageType sourceImage;
    ImageType markerImage;
    ImageType expectedImage;

public:
    TestData(unsigned int width, unsigned int height)
            : sourceImage(width, height), markerImage(width, height),
            expectedImage(width, height) {
    }

    void useHorizontalLine(PixelType background, PixelType sourceForeground,
            PixelType expectedForeground) {
        const unsigned int halfHeight = sourceImage.getHeight() / 2;
        const unsigned int maxX = sourceImage.getWidth() - 1;
        const unsigned int startX = 1;
        const unsigned int startY = halfHeight;
        const unsigned int endX = maxX - 1;
        const unsigned int endY = halfHeight;

        useRectangle(startX, startY, endX, endY, background, sourceForeground,
                expectedForeground);
    }

    void useVerticalLine(PixelType background, PixelType sourceForeground,
            PixelType expectedForeground) {
        const unsigned int halfWidth = sourceImage.getWidth() / 2;
        const unsigned int maxY = sourceImage.getHeight() - 1;
        const unsigned int startX = halfWidth;
        const unsigned int startY = 1;
        const unsigned int endX = halfWidth;
        const unsigned int endY = maxY - 1;

        useRectangle(startX, startY, endX, endY, background, sourceForeground,
                expectedForeground);
    }

    void useRectangle(PixelType background, PixelType sourceForeground,
            PixelType expectedForeground) {
        const unsigned int maxX = sourceImage.getWidth() - 1;
        const unsigned int maxY = sourceImage.getHeight() - 1;
        const unsigned int startX = 1;
        const unsigned int startY = 1;
        const unsigned int endX = maxX - 1;
        const unsigned int endY = maxY - 1;

        useRectangle(startX, startY, endX, endY, background, sourceForeground,
                expectedForeground);
    }

    void useRectangle(unsigned int startX, unsigned int startY,
            unsigned int endX, unsigned int endY, PixelType background,
            PixelType sourceForeground, PixelType expectedForeground) {
        sourceImage = [=] (unsigned int x, unsigned int y) -> PixelType {
            if (x >= startX && y >= startY && x <= endX && y <= endY)
                return sourceForeground;
            else
                return background;
        };

        expectedImage = [=] (unsigned int x, unsigned int y) -> PixelType {
            if (x >= startX && y >= startY && x <= endX && y <= endY)
                return expectedForeground;
            else
                return background;
        };
    }

    void setMarker(PixelType background, const Pixel& pixel) {
        markerImage = [background] (unsigned int, unsigned int) -> PixelType {
            return background;
        };

        unsigned int x;
        unsigned int y;
        PixelType value;

        std::tie(x, y, value) = pixel;

        markerImage.setPixel(x, y, value);
    }

    void applyFilterAndVerifyResult() {
        filter.apply(sourceImage, markerImage);

        assertThat(markerImage).isEqualTo(expectedImage);
    }
};

#endif
