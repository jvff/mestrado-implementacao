#include <gtest/gtest.h>

#include "asserts.hpp"

#include "GrayscaleImage.hpp"

TEST(GrayscaleImageTest, type) {
    AssertThat<GrayscaleImage>::isSubClass(Of<Image<int> >());
}
