#ifndef MAX_TREE_IMAGE_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_IMAGE_NODE_REMOVAL_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImage.hpp"

#include "DummyTypes.hpp"
#include "MaxTreeImageTest.hpp"

class MaxTreeImageNodeRemovalTest : public MaxTreeImageTest {
protected:
    void verifyFilledImagePixels(Image<PixelType>& image, PixelType color) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                assertThat(image.getPixelValue(x, y)).isEqualTo(color);
        }
    }
};

#endif
