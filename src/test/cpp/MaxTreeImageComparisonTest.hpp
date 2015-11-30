#ifndef MAX_TREE_IMAGE_COMPARISON_TEST_HPP
#define MAX_TREE_IMAGE_COMPARISON_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

class MaxTreeImageComparisonTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;

protected:
    void createDefaultTreeFor(DummyMaxTreeImageType& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0l; y < height; ++y)
                image.assignPixelToLatestNode(x, y);
        }
    }
};

#endif
