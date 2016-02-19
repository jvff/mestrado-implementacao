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

    template <typename T>
    using PixelList = std::initializer_list<Pixel<T> >;

protected:
    template <typename PixelType>
    void verifyOrder(PixelList<PixelType> orderedList) {
        std::vector<Pixel<PixelType> > orderedPixels(orderedList);
        const auto start = orderedPixels.begin();
        const auto end = orderedPixels.end();

        for (auto position = start; position != end; ++position)
            verifyOrderAtPosition<PixelType>(start, position, end);
    }

private:
    template <typename PixelType>
    void verifyOrderAtPosition(const Iterator<PixelType>& start,
            const Iterator<PixelType>& position,
            const Iterator<PixelType>& end) {
        auto pixel = *position;

        compareSinglePixel(pixel);

        verifyPixelsBeforePixel(pixel, start, position);
        verifyPixelsAfterPixel(pixel, position + 1, end);
    }

    template <typename PixelType>
    void verifyPixelsBeforePixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end) {
        for (auto position = start; position != end; ++position)
            compareTwoPixels(*position, pixel);
    }

    template <typename PixelType>
    void verifyPixelsAfterPixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end) {
        for (auto position = start; position != end; ++position)
            compareTwoPixels(pixel, *position);
    }

    template <typename PixelType>
    void compareSinglePixel(const Pixel<PixelType>& pixel) const {
        assertThat(pixel).isNotLessThan(pixel);
        assertThat(pixel).isNotGreaterThan(pixel);
    }

    template <typename PixelType>
    void compareTwoPixels(const Pixel<PixelType>& before,
            const Pixel<PixelType>& after) const {
        assertThat(before).isLessThan(after);
        assertThat(before).isNotGreaterThan(after);
        assertThat(after).isGreaterThan(before);
        assertThat(after).isNotLessThan(before);
    }
};

#endif
