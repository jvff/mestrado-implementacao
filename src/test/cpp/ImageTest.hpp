#ifndef IMAGE_TEST_H
#define IMAGE_TEST_H

#include <gtest/gtest.h>

#include "Image.hpp"

template <typename ImageType>
class ImageTest : public ::testing::Test {
protected:
    void testSinglePixel(int color);
    void testPixelsWithSameColor(int width, int height, int color);
    void testPixels(int width, int height, const int colors[]);
};

#endif
