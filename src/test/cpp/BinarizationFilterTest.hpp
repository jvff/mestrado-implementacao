#ifndef BINARIZATION_FILTER_TEST_HPP
#define BINARIZATION_FILTER_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename T>
class EqualsComparator {
public:
    bool operator() (const T& first, const T& second) {
        return first == second;
    }
};

template <typename SourcePixel,
        template <typename> class ComparatorTemplate = std::greater>
class TestImage : public Image<SourcePixel> {
public:
    using Comparator = ComparatorTemplate<SourcePixel>;

    SimpleArrayImage<SourcePixel> sourceImage;
    SimpleArrayImage<bool> expectedImage;
    SourcePixel filterThreshold;
    Comparator comparator;

    TestImage(unsigned int width, unsigned int height,
            const SourcePixel& threshold)
            : Image<SourcePixel>(width, height), sourceImage(width, height),
            expectedImage(width, height), filterThreshold(threshold) {
        *this = [] (unsigned int x, unsigned int y) {
            return (int)x - (int)y;
        };
    }

    using Image<SourcePixel>::operator=;

    SourcePixel getPixelValue(unsigned int x, unsigned int y) const override {
        return sourceImage.getPixelValue(x, y);
    }

    void setPixel(unsigned int x, unsigned int y, SourcePixel value) override {
        sourceImage.setPixel(x, y, value);
        expectedImage.setPixel(x, y, comparator(value, filterThreshold));
    }
};

#endif
