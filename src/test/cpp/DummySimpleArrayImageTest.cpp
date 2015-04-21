#include <gtest/gtest.h>

#include "DummySimpleArrayImage.hpp"

TEST(DummySimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image = new DummySimpleArrayImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}
