#include "OpenCLImageTypeTests.hpp"

TEST_C(classTemplateExists) {
    AssertThat<ImageType>::isClassOrStruct();
}

TEST_C(isImage) {
    using ParentImageType = Image<PixelType>;

    AssertThat<ImageType>::isSubClass(Of<ParentImageType>());
}

TEST_C(hasConstructor) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;
    using ContextParameter = cl::Context&;
    using CommandQueueParameter = cl::CommandQueue&;

    AssertThat<ImageType>::isConstructible(With<WidthParameter, HeightParameter,
            ContextParameter, CommandQueueParameter>());
}

TEST_C(usesCorrectPixelBufferSize) {
    using FakeImageType = FakeOpenCLImage<PixelType>;
    using PixelTypeData = OpenCLPixelTypeData<PixelType>;

    constexpr auto pixelBufferSize = FakeImageType::pixelBufferSize;
    constexpr auto expectedPixelBufferSize =
                PixelTypeData::CL_PIXEL_BUFFER_SIZE;

    assertThat(pixelBufferSize).isEqualTo(expectedPixelBufferSize);
}
