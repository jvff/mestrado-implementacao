#include <CL/cl.hpp>
#include <CL/opencl.h>

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

TEST(OpenCLImageTest, hasConstructor) {
    using PixelType = unsigned char;
    using ImageType = OpenCLImage<PixelType>;
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;
    using ContextParameter = cl::Context&;
    using CommandQueueParameter = cl::CommandQueue&;

    AssertThat<ImageType>::isConstructible(With<WidthParameter, HeightParameter,
            ContextParameter, CommandQueueParameter>());
}
