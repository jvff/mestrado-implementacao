#ifndef RGB_IMAGE_TEST_H
#define RGB_IMAGE_TEST_H

#include "ImageTest.hpp"

template <typename ImageType>
class RgbImageTest : public ImageTest<ImageType, int> {
protected:
    virtual void comparePixel(int a, int b) {
        EXPECT_EQ(a, b);
    }
};

#endif
