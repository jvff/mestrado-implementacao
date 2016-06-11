#include "LuminanceFilterTest.hpp"

TEST_F(LuminanceFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(LuminanceFilterTest, isSubClassOfFilter) {
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_F(LuminanceFilterTest, rgbSpecializationIsSubClassOfSimpleFilter) {
    using SourcePixelType = unsigned char;
    using InternalImageType = Image<SourcePixelType>;
    using SourceImageType = RgbImage<InternalImageType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_F(LuminanceFilterTest, doesntChangeImage) {
    using PixelType = DummyType;
    using SourceImageType = Image<PixelType>;
    using DestinationImageType = SimpleArrayImage<PixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;

    unsigned int width = 4;
    unsigned int height = 3;

    DummyFilter filter;
    SimpleArrayImage<PixelType> image(width, height);
    const Image<PixelType>& sourceImage = image;

    image = [=] (unsigned int x, unsigned int y) -> DummyType {
        return DummyType{ (int)(x + y * width) };
    };

    auto resultingImage = filter.apply(image);

    assertThat(resultingImage).isEqualTo(sourceImage);
}

TEST_F(LuminanceFilterTest, handlesRgbImages) {
    using SourcePixelChannelType = std::uint16_t;
    using SourcePixelType = std::uint64_t;
    using DestinationPixelType = unsigned char;
    using InternalImageType = SimpleArrayImage<SourcePixelType>;
    using SourceImageType = RgbImage<InternalImageType>;
    using DestinationImageType = SimpleArrayImage<DestinationPixelType>;
    using FilterType = LuminanceFilter<SourceImageType, DestinationImageType>;

    unsigned int width = 8;
    unsigned int height = 8;

    FilterType filter;
    Mock<SourceImageType> sourceImageMock;
    SimpleArrayImage<DestinationPixelType> expectedImage(width, height);

    When(Method(sourceImageMock, getWidth)).AlwaysReturn(width);
    When(Method(sourceImageMock, getHeight)).AlwaysReturn(height);

    SourcePixelType maximumChannelValue =
            std::numeric_limits<SourcePixelChannelType>::max();
    float componentFactor = 1.f / (float)maximumChannelValue;
    float pixelFactor = std::numeric_limits<DestinationPixelType>::max();

    SourcePixelType channelValues[4];

    channelValues[0] = 0;
    channelValues[1] = maximumChannelValue / 3;
    channelValues[2] = maximumChannelValue * 2 / 3;
    channelValues[3] = maximumChannelValue;

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

            float redRelativeComponent = redComponent * componentFactor;
            float greenRelativeComponent = greenComponent * componentFactor;
            float blueRelativeComponent = blueComponent * componentFactor;

            float redContribution = 0.2126f * redRelativeComponent;
            float greenContribution = 0.7152f * greenRelativeComponent;;
            float blueContribution = 0.0722f * blueRelativeComponent;;

            float relativeLuminance = 0.f;

            relativeLuminance += redContribution;
            relativeLuminance += greenContribution;
            relativeLuminance += blueContribution;

            DestinationPixelType luminanceValue =
                    std::round(relativeLuminance * pixelFactor);

            When(Method(sourceImageMock, getRelativeRedComponent).Using(x, y))
                .AlwaysReturn(redRelativeComponent);

            When(Method(sourceImageMock, getRelativeGreenComponent).Using(x, y))
                .AlwaysReturn(greenRelativeComponent);

            When(Method(sourceImageMock, getRelativeBlueComponent).Using(x, y))
                .AlwaysReturn(blueRelativeComponent);

            expectedImage.setPixel(x, y, luminanceValue);
        }
    }

    const SourceImageType& sourceImage = sourceImageMock.get();
    auto resultingImage = filter.apply(sourceImage);

    assertThat(resultingImage).isEqualTo(expectedImage);
}
