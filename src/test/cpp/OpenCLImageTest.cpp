#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "OpenCLImage.hpp"

TEST(OpenCLImageTest, classTemplateExists) {
    using PixelType = unsigned char;
    using ImageType = OpenCLImage<PixelType>;

    AssertThat<ImageType>::isClassOrStruct();
}

TEST(OpenCLImageTest, isImage) {
    using PixelType = unsigned char;
    using ImageType = OpenCLImage<PixelType>;
    using ParentImageType = Image<PixelType>;

    AssertThat<ImageType>::isSubClass(Of<ParentImageType>());
}
