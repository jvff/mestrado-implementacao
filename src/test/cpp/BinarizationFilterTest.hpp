#ifndef BINARIZATION_FILTER_TEST_HPP
#define BINARIZATION_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "BinarizationFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename SourcePixel>
class TestImage : public Image<SourcePixel> {
public:
    using Comparator =
            std::function<bool(const SourcePixel&, const SourcePixel&)>;

    SimpleArrayImage<SourcePixel> sourceImage;
    SimpleArrayImage<bool> expectedImage;
    SourcePixel filterThreshold;
    Comparator comparator;

    static bool defaultComparator(const SourcePixel& value,
            const SourcePixel& threshold) {
        return value >= threshold;
    }

    TestImage(unsigned int width, unsigned int height,
            const SourcePixel& threshold)
            : TestImage(width, height, threshold, defaultComparator) {
    }

    TestImage(unsigned int width, unsigned int height,
            const SourcePixel& threshold, const Comparator& customComparator)
            : Image<SourcePixel>(width, height), sourceImage(width, height),
            expectedImage(width, height), filterThreshold(threshold),
            comparator(customComparator) {
        *this = [] (unsigned int x, unsigned int y) {
            return (int)x - (int)y;
        };
    }

    using Image<SourcePixel>::operator=;

    SourcePixel getPixel(unsigned int x, unsigned int y) const override {
        return sourceImage.getPixel(x, y);
    }

    void setPixel(unsigned int x, unsigned int y, SourcePixel value) override {
        sourceImage.setPixel(x, y, value);
        expectedImage.setPixel(x, y, comparator(value, filterThreshold));
    }
};

#endif
