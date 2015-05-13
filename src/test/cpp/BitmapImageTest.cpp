#include <gtest/gtest.h>

#include "BitmapImage.hpp"

TEST(BitmapImageTest, typeIsImage) {
    EXPECT_TRUE((std::is_base_of<Image<bool>, BitmapImage>::value));
}
