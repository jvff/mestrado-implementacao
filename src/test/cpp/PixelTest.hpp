#ifndef PIXEL_TEST_HPP
#define PIXEL_TEST_HPP

#include <initializer_list>
#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Pixel.hpp"

#include "AssertionsSpecificForPixel.hpp"
#include "DummyTypes.hpp"

class PixelTest : public ::testing::Test {
protected:
    template <typename T>
    using Iterator = typename std::vector<Pixel<T> >::iterator;

protected:
    template <typename PixelType>
    void verifyOrder(std::initializer_list<Pixel<PixelType> > orderedList) {
        std::vector<Pixel<PixelType> > orderedPixels(orderedList);
        const auto start = orderedPixels.begin();
        const auto end = orderedPixels.end();

        for (auto position = start; position != end; ++position)
            verifyOrderAtPosition<PixelType>(start, position, end);
    }

    template <typename PixelType>
    void verifyOrderAtPosition(const Iterator<PixelType>& start,
            const Iterator<PixelType>& position,
            const Iterator<PixelType>& end) {
        auto pixel = *position;

        verifyPixelsBeforePixel(pixel, start, position);
        verifyOrderOfSinglePixel(pixel);
        verifyPixelsAfterPixel(pixel, position + 1, end);
    }

    template <typename PixelType>
    void verifyPixelsBeforePixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end) {
        for (auto position = start; position != end; ++position)
            verifyOrderOfTwoPixels(*position, pixel);
    }

    template <typename PixelType>
    void verifyPixelsAfterPixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end) {
        for (auto position = start; position != end; ++position)
            verifyOrderOfTwoPixels(pixel, *position);
    }

    template <typename PixelType>
    void verifyOrderOfSinglePixel(const Pixel<PixelType>& pixel) {
        assertThat(pixel).isNotBefore(pixel);
        assertThat(pixel).isNotAfter(pixel);
    }

    template <typename PixelType>
    void verifyOrderOfTwoPixels(const Pixel<PixelType>& before,
            const Pixel<PixelType>& after) {
        assertThat(before).isBefore(after);
        assertThat(before).isNotAfter(after);
        assertThat(after).isAfter(before);
        assertThat(after).isNotBefore(before);
    }
};

#endif
