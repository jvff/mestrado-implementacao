#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

TEST(RgbImageTest, type) {
    AssertThat<RgbImage>::isSubClass(Of<Image<int> >());
}
