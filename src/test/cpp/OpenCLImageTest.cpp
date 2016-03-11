#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLImage.hpp"

TEST(OpenCLImageTest, classTemplateExists) {
    using PixelType = unsigned char;
    using ImageType = OpenCLImage<PixelType>;

    AssertThat<ImageType>::isClassOrStruct();
}
