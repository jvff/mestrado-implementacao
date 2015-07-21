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
    SimpleArrayImage<SourcePixel> sourceImage;
    SimpleArrayImage<bool> expectedImage;
    SourcePixel filterThreshold;

    TestImage(unsigned int width, unsigned int height,
            const SourcePixel& threshold) : Image<SourcePixel>(width, height),
            sourceImage(width, height), expectedImage(width, height),
            filterThreshold(threshold) {
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
        expectedImage.setPixel(x, y, value >= filterThreshold);
    }
};

#endif
