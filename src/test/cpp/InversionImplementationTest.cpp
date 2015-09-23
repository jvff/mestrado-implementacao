#include "InversionImplementationTest.hpp"

TEST_F(InversionImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(InversionImplementationTest, isFilterImplementation) {
    using ImplementationType = DummyImplementation;
    using FilterImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<FilterImplementationType>());
}

TEST_F(InversionImplementationTest, canBeConstructedWithoutExtraParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(With<SourceImageParameter,
            DestinationImageParameter>());
}

TEST_F(InversionImplementationTest, canBeConstructedWithOptionalParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;
    using MinimumValueParameter = const SourcePixelType&;
    using MaximumValueParameter = const SourcePixelType&;

    AssertThat<DummyImplementation>::isConstructible(With<SourceImageParameter,
            DestinationImageParameter, MinimumValueParameter,
            MaximumValueParameter>());
}

TEST_F(InversionImplementationTest, uniformImageIsntChanged) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 100)
        .setPixel(0, 1, 100)
        .setPixel(1, 0, 100)
        .setPixel(1, 1, 100);
}

TEST_F(InversionImplementationTest, pixelsAreSwapped) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 12)
        .setPixel(0, 1, 200)
        .setPixel(1, 0, 200)
        .setPixel(1, 1, 12);
}

TEST_F(InversionImplementationTest, pixelsAreSwappedAndMiddleValueIsKept) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 12)
        .setPixel(0, 1, 106)
        .setPixel(1, 0, 106)
        .setPixel(1, 1, 200);
}

TEST_F(InversionImplementationTest, imageWithDifferentPixels) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 92)
        .setPixel(0, 1, 100)
        .setPixel(1, 0, 145)
        .setPixel(1, 1, 200);
}

TEST_F(InversionImplementationTest, uniformImageIsDisplacedByCustomRange) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setRange(36, 140)
        .setPixel(0, 0, 37)
        .setPixel(0, 1, 37)
        .setPixel(1, 0, 37)
        .setPixel(1, 1, 37);
}

TEST_F(InversionImplementationTest, imageWithDifferentPixelsAndCustomRange) {
    TestData<unsigned char>()
        .setDimensions(2, 2)
        .setRange(22, 250)
        .setPixel(0, 0, 40)
        .setPixel(0, 1, 34)
        .setPixel(1, 0, 89)
        .setPixel(1, 1, 200);
}
