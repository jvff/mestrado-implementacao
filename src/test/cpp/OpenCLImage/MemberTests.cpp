#include "OpenCLImageMemberTests.hpp"

TEST_C(contextIsAccessible) {
    const auto image = ImageType(1, 1, context, commandQueue);

    auto& imageContext = image.getContext();

    assertThat(imageContext).isAtSameAddressAs(context);
}

TEST_C(commandQueueIsAccessible) {
    const auto image = ImageType(1, 1, context, commandQueue);

    auto& imageCommandQueue = image.getCommandQueue();

    assertThat(imageCommandQueue).isAtSameAddressAs(commandQueue);
}

TEST_C(imageBufferIsAccessible) {
    auto width = 42u;
    auto height = 23u;

    const auto image = ImageType(width, height, context, commandQueue);

    auto& imageBuffer = image.getImageBuffer();

    auto bufferWidth = imageBuffer.getImageInfo<CL_IMAGE_WIDTH>();
    auto bufferHeight = imageBuffer.getImageInfo<CL_IMAGE_HEIGHT>();
    auto bufferFormat = imageBuffer.getImageInfo<CL_IMAGE_FORMAT>();
    auto bufferChannelOrder = bufferFormat.image_channel_order;
    auto bufferChannelType = bufferFormat.image_channel_data_type;

    assertThat(bufferWidth).isEqualTo(width);
    assertThat(bufferHeight).isEqualTo(height);
    assertThat(bufferChannelOrder).isEqualTo((unsigned int)CL_R);
    assertThat(bufferChannelType).isEqualTo((unsigned int)CL_UNSIGNED_INT8);
}

TEST_C(handlesCanBeUsedToCreateNewImage) {
    const auto firstImage = ImageType(12, 23, context, commandQueue);
    const auto secondImage = ImageType(21, 32, context, commandQueue);

    auto& firstContext = firstImage.getContext();
    auto& secondContext = secondImage.getContext();

    auto& firstCommandQueue = firstImage.getCommandQueue();
    auto& secondCommandQueue = secondImage.getCommandQueue();

    assertThat(firstContext).isAtSameAddressAs(secondContext);
    assertThat(firstCommandQueue).isAtSameAddressAs(secondCommandQueue);
}
