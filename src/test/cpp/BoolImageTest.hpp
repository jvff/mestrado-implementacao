#ifndef BOOL_IMAGE_TEST_HPP
#define BOOL_IMAGE_TEST_HPP

#include "ImageTest.hpp"

template <typename ImageType>
class BoolImageTest : public ImageTest<ImageType, bool> {
protected:
    virtual void comparePixel(bool a, bool b) {
        EXPECT_EQ(a, b);
    }
};

#endif
