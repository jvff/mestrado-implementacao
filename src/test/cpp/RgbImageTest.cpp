#include <gtest/gtest.h>

#include "RgbImage.hpp"

TEST(RgbImageTest, type) {
    EXPECT_TRUE((std::is_base_of<Image<int>, RgbImage>::value));
}
