#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaOpeningImplementationTest, classTemplateExists) {
    using PixelType = DummyType;
    using ImageType = FakeImage<PixelType>;
    using ImplementationClass = AreaOpeningImplementation<PixelType,
            PixelType, ImageType>;

    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST(AreaOpeningImplementationTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = AreaOpeningImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = AreaOpeningImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(AreaOpeningImplementationTest, isConstructibleWithParameters) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = AreaOpeningImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const Image<SourcePixelType>&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationType>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}

TEST(AreaOpeningImplementationTest, bigPlateauIsntCleared) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using ImplementationType = AreaOpeningImplementation<PixelType, PixelType,
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
