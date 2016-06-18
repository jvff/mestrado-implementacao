#include "LuminanceFilterRgbImageImplementationTest.hpp"

using TypeParameters = ::testing::Types<
        Aliases<RgbImage<SimpleArrayImage<std::uint64_t> >,
                RgbImage<SimpleArrayImage<std::uint64_t> >,
                SimpleArrayImage<unsigned char> >,
        Aliases<RgbImage<OpenCLImage<std::uint64_t> >,
                RgbImage<OpenCLImage<std::uint64_t> >,
                OpenCLImage<std::uint64_t> > >;

TYPED_TEST_CASE(LuminanceFilterRgbImageImplementationTest, TypeParameters);

TEST_C(handlesRgbImages) {
    using DestinationPixelType = typename DestinationImageType::PixelType;

    unsigned int width = 8;
    unsigned int height = 8;

    FilterType filter;

    auto internalImage = createInternalImage(width, height);
    auto sourceImage = SourceImageType(internalImage, true);
    auto expectedImage = createDestinationImage(width, height);

    float pixelFactor = std::numeric_limits<DestinationPixelType>::max();

    float channelValues[4] = { 0.f, 0.33f, 0.67f, 1.f };

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto tileX = x / 4;
            auto tileY = y / 4;
            auto tileId = tileX + tileY * 2;
            auto xInTile = x % 4;
            auto yInTile = y % 4;

            float redComponent = channelValues[xInTile];
            float greenComponent = channelValues[yInTile];
            float blueComponent = channelValues[tileId];

            sourceImage.setPixel(x, y, redComponent, greenComponent,
                    blueComponent);

            auto updatedRedComponent =
                    sourceImage.getRelativeRedComponent(x, y);
            auto updatedGreenComponent =
                    sourceImage.getRelativeGreenComponent(x, y);
            auto updatedBlueComponent =
                    sourceImage.getRelativeBlueComponent(x, y);

            float redContribution = 0.2126f * updatedRedComponent;
            float greenContribution = 0.7152f * updatedGreenComponent;;
            float blueContribution = 0.0722f * updatedBlueComponent;;

            float relativeLuminance = 0.f;

            relativeLuminance += redContribution;
            relativeLuminance += greenContribution;
            relativeLuminance += blueContribution;

            auto luminanceValue = std::round(relativeLuminance * pixelFactor);
            auto expectedValue = convertFloatDestinationValue(luminanceValue);

            expectedImage.setPixel(x, y, expectedValue);
        }
    }

    auto resultingImage = filter.apply(sourceImage);

    assertThat(resultingImage).isEqualTo(expectedImage);
}
