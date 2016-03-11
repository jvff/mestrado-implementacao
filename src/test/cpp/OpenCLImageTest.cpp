#include "OpenCLImageTest.hpp"

TEST_F(OpenCLImageTest, classTemplateExists) {
    AssertThat<ImageType>::isClassOrStruct();
}

TEST_F(OpenCLImageTest, isImage) {
    using ParentImageType = Image<PixelType>;

    AssertThat<ImageType>::isSubClass(Of<ParentImageType>());
}

TEST_F(OpenCLImageTest, hasConstructor) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;
    using ContextParameter = cl::Context&;
    using CommandQueueParameter = cl::CommandQueue&;

    AssertThat<ImageType>::isConstructible(With<WidthParameter, HeightParameter,
            ContextParameter, CommandQueueParameter>());
}
