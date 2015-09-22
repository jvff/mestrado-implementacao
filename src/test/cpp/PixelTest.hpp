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

private:
    template <typename PixelType>
    struct Comparator {
        virtual void compareSinglePixel(const Pixel<PixelType>& pixel) const
                = 0;
        virtual void compareTwoPixels(const Pixel<PixelType>& before,
                const Pixel<PixelType>& after) const = 0;
    };

    template <typename PixelType>
    struct DirectComparator : public Comparator<PixelType> {
        void compareSinglePixel(const Pixel<PixelType>& pixel) const override {
            assertThat(pixel).isNotBefore(pixel);
            assertThat(pixel).isNotAfter(pixel);
        }

        void compareTwoPixels(const Pixel<PixelType>& before,
                const Pixel<PixelType>& after) const override {
            assertThat(before).isBefore(after);
            assertThat(before).isNotAfter(after);
            assertThat(after).isAfter(before);
            assertThat(after).isNotBefore(before);
        }
    };

    template <typename PixelType, typename ComparatorClass, bool isAscending>
    struct IndirectComparator : public Comparator<PixelType> {
        ComparatorClass compare;

        void compareSinglePixel(const Pixel<PixelType>& pixel) const override {
            assertThat(compare(pixel, pixel)).isEqualTo(false);
        }

        void compareTwoPixels(const Pixel<PixelType>& before,
                const Pixel<PixelType>& after) const override {
            const bool isDescending = !isAscending;

            assertThat(compare(before, after)).isEqualTo(isAscending);
            assertThat(compare(after, before)).isEqualTo(isDescending);
        }
    };

    template <typename PixelType>
    struct IndirectAscendingComparator : public IndirectComparator<PixelType,
            typename Pixel<PixelType>::AscendingComparator, true> {
    };

    template <typename PixelType>
    struct IndirectDescendingComparator : public IndirectComparator<PixelType,
            typename Pixel<PixelType>::DescendingComparator, false> {
    };

protected:
    template <typename PixelType>
    void verifyOrder(PixelList<PixelType> orderedList) {
        verifyOrder(orderedList, DirectComparator<PixelType>());
    }

    template <typename PixelType>
    void verifyOrderUsingAscendingComparator(PixelList<PixelType> orderedList) {
        verifyOrder(orderedList, IndirectAscendingComparator<PixelType>());
    }

    template <typename PixelType>
    void verifyOrderUsingDescendingComparator(
            PixelList<PixelType> orderedList) {
        verifyOrder(orderedList, IndirectDescendingComparator<PixelType>());
    }

private:
    template <typename PixelType>
    void verifyOrder(PixelList<PixelType> orderedList,
            const Comparator<PixelType>& comparator) {
        std::vector<Pixel<PixelType> > orderedPixels(orderedList);
        const auto start = orderedPixels.begin();
        const auto end = orderedPixels.end();

        for (auto position = start; position != end; ++position)
            verifyOrderAtPosition<PixelType>(start, position, end, comparator);
    }

    template <typename PixelType>
    void verifyOrderAtPosition(const Iterator<PixelType>& start,
            const Iterator<PixelType>& position,
            const Iterator<PixelType>& end,
            const Comparator<PixelType>& comparator) {
        auto pixel = *position;

        verifyPixelsBeforePixel(pixel, start, position, comparator);
        comparator.compareSinglePixel(pixel);
        verifyPixelsAfterPixel(pixel, position + 1, end, comparator);
    }

    template <typename PixelType>
    void verifyPixelsBeforePixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end,
            const Comparator<PixelType>& comparator) {
        for (auto position = start; position != end; ++position)
            comparator.compareTwoPixels(*position, pixel);
    }

    template <typename PixelType>
    void verifyPixelsAfterPixel(const Pixel<PixelType>& pixel,
            const Iterator<PixelType>& start, const Iterator<PixelType>& end,
            const Comparator<PixelType>& comparator) {
        for (auto position = start; position != end; ++position)
            comparator.compareTwoPixels(pixel, *position);
    }
};

#endif
