#include "AreaOpeningImplementationTest.hpp"

TEST_F(AreaOpeningImplementationTest, classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST_F(AreaOpeningImplementationTest, isFilterImplementation) {
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(AreaOpeningImplementationTest, isConstructibleWithParameters) {
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const Image<SourcePixelType>&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationClass>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}

TEST_F(AreaOpeningImplementationTest, bigPlateauIsntCleared) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using ImplementationType = AreaOpeningImplementation<Image<PixelType>,
            ImageType>;

    const unsigned int maximumPeakSize = 9;
    const unsigned int imageSize = 6;
    const unsigned int squareSize = 4;

    const unsigned int squareStart = 1;
    const unsigned int squareEnd = squareStart + squareSize - 1;

    ImageType sourceImage(imageSize, imageSize);
    ImageType resultingImage(imageSize, imageSize);
    ImageType& expectedImage = sourceImage;

    sourceImage = [] (unsigned int x, unsigned int y) {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return 167;
        } else
            return 102;
    };

    ImplementationType implementation(maximumPeakSize, sourceImage,
            resultingImage);

    implementation.apply();

    assertThat(resultingImage).isEqualTo(expectedImage);
}

TEST_F(AreaOpeningImplementationTest, smallPlateauIsCleared) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using ImplementationType = AreaOpeningImplementation<Image<PixelType>,
            ImageType>;

    const unsigned int maximumPeakSize = 12;
    const unsigned int imageSize = 6;
    const unsigned int squareSize = 2;

    const unsigned int squareStart = 1;
    const unsigned int squareEnd = squareStart + squareSize - 1;

    const PixelType plateauHeight = 201;
    const PixelType floorHeight = 13;

    ImageType sourceImage(imageSize, imageSize);
    ImageType resultingImage(imageSize, imageSize);
    ImageType expectedImage(imageSize, imageSize);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return plateauHeight;
        } else
            return floorHeight;
    };

    expectedImage = [] (unsigned int, unsigned int) -> PixelType {
        return floorHeight;
    };

    ImplementationType implementation(maximumPeakSize, sourceImage,
            resultingImage);

    implementation.apply();

    assertThat(resultingImage).isEqualTo(expectedImage);
}
