#include "ImagePaintWithImageTest.hpp"

TEST_P(ImagePaintWithImageTest, isAssignable) {
    auto destinationImage = FakeDummyImage(destinationWidth, destinationHeight);
    auto destinationImageSpy = spyImage(destinationImage);

    auto sourceImageMock = createMockImage(sourceWidth, sourceHeight);
    const auto& sourceImage = sourceImageMock.get();

    destinationImage.paint(sourceImage);

    verifyImageWasRead(sourceImageMock);
    verifyImageWasPainted(destinationImageSpy);
}

static ImageConfigurations imagesWithSameSize = { 3, 5, 3, 5 };
static ImageConfigurations assignToLargerImage = { 3, 2, 5, 4 };
static ImageConfigurations assignToSmallerImage = { 9, 7, 7, 6 };
static ImageConfigurations assignToWiderImage = { 4, 3, 9, 3 };
static ImageConfigurations assignToNarrowerImage = { 5, 4, 4, 4 };
static ImageConfigurations assignToTallerImage = { 2, 3, 2, 4 };
static ImageConfigurations assignToShorterImage = { 3, 5, 3, 2 };
static ImageConfigurations assignToShorterWiderImage = { 4, 5, 3, 2 };
static ImageConfigurations assignToTallerNarrowerImage = { 4, 2, 2, 3 };

INSTANTIATE_TEST_CASE_P(ImagePaintWithImageTestInstantiation,
        ImagePaintWithImageTest,
        testing::Values(
            imagesWithSameSize,
            assignToLargerImage,
            assignToSmallerImage,
            assignToWiderImage,
            assignToNarrowerImage,
            assignToTallerImage,
            assignToShorterImage,
            assignToShorterWiderImage,
            assignToTallerNarrowerImage
        ));
