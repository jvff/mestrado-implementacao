#include "OpenCLImageTest.hpp"

cl::Context OpenCLImageTest::context;
cl::CommandQueue OpenCLImageTest::commandQueue;

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

TEST_F(OpenCLImageTest, contextIsAccessible) {
    auto image = ImageType(1, 1, context, commandQueue);

    auto& imageContext = image.getContext();

    assertThat(imageContext).isAtSameAddressAs(context);
}

TEST_F(OpenCLImageTest, commandQueueIsAccessible) {
    auto image = ImageType(1, 1, context, commandQueue);

    auto& imageCommandQueue = image.getCommandQueue();

    assertThat(imageCommandQueue).isAtSameAddressAs(commandQueue);
}
