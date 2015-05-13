#include <gtest/gtest.h>

#include "GrayscaleImage.hpp"

TEST(GrayscaleImageTest, type) {
    EXPECT_TRUE((std::is_base_of<Image<int>, GrayscaleImage>::value));
}
