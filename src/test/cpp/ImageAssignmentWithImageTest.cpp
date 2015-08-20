#include "ImageAssignmentWithImageTest.hpp"

TEST_P(ImageAssignmentWithImageTest, isAssignable) {
    auto destinationImage = FakeDummyImage(destinationWidth, destinationHeight);
    auto destinationImageSpy = spyImage(destinationImage);

    auto sourceImageMock = createMockImage(sourceWidth, sourceHeight);
    const auto& sourceImage = sourceImageMock.get();

    destinationImage = sourceImage;

    verifyImageWasRead(sourceImageMock);
    verifyImageWasPainted(destinationImageSpy);
}

static ImageConfigurations imagesWithSameSize = { 3, 5, 3, 5 };
static ImageConfigurations assignToLargerImage = { 3, 2, 5, 4 };
static ImageConfigurations assignToSmallerImage = { 9, 7, 7, 6 };

INSTANTIATE_TEST_CASE_P(ImageAssignmentWithImageTestInstantiation,
        ImageAssignmentWithImageTest,
        testing::Values(
            imagesWithSameSize,
            assignToLargerImage,
            assignToSmallerImage
        ));
