#include "MaxTreeImplementationTest.hpp"

TEST_F(MaxTreeImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(MaxTreeImplementationTest, isFilterImplementation) {
    using ParentClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isSubClass(Of<ParentClass>());
}

TEST_F(MaxTreeImplementationTest, isConstructibleWithParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementationType>::isConstructible(With<
            SourceImageParameter, DestinationImageParameter>());
}

TEST_F(MaxTreeImplementationTest, allNodesAreAssignedToRootNode) {
    using PixelType = unsigned char;
    using SourceImageType = SimpleArrayImage<PixelType>;
    using DestinationImageType = MaxTreeImage<SourceImageType>;
    using ImplementationType = MaxTreeImplementation<SourceImageType,
            SourceImageType>;

    unsigned int width = 4;
    unsigned int height = 2;
    PixelType imageColor = 8;

    SourceImageType sourceImage(width, height);
    DestinationImageType destinationImage(width, height);
    ImplementationType implementation(sourceImage, destinationImage);

    sourceImage = [imageColor] (unsigned int, unsigned int) -> PixelType {
        return imageColor;
    };

    implementation.apply();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto node = destinationImage.getNodeOfPixel(x, y);
            unsigned int expectedId = 0;

            assertThat(node.level).isEqualTo(imageColor);
            assertThat(node.id).isEqualTo(expectedId);
            assertThat((bool)node.parent).isEqualTo(false);
        }
    }
}
