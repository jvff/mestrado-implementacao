#ifndef RGB_IMAGE_TEST_HPP
#define RGB_IMAGE_TEST_HPP

#include "ImageTest.hpp"

template <typename ImageType>
class RgbImageTest : public ImageTest<ImageType, int> {
protected:
    virtual void comparePixel(int a, int b) {
        EXPECT_EQ(a, b);
    }
};

#endif
