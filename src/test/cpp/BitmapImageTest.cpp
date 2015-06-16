#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BitmapImage.hpp"

TEST(BitmapImageTest, typeIsImage) {
    AssertThat<BitmapImage>::isSubClass(Of<Image<bool> >());
}
