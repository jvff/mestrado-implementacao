#include "HminImplementationTest.hpp"

TEST_F(HminImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(HminImplementationTest, isFilterImplementation) {
    using ImplementationClass = HminImplementation<SourceImageType,
            DestinationImageType>;
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(HminImplementationTest, isConstructibleWithParameters) {
    using FeatureSizeParameter = const SourcePixelType&;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(With<FeatureSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}

TEST_F(HminImplementationTest, removesShallowHole) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(4)
        .setBackground(24)
        .drawSquare(1, 1, 5, 21)
        .setExpectedBackground(25);
}

TEST_F(HminImplementationTest, doesntChangePeak) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(2)
        .setBackground(134)
        .drawSquare(1, 1, 5, 231)
        .setExpectedBackground(136)
        .drawExpectedSquare(1, 1, 5, 231);
}

TEST_F(HminImplementationTest, shavesValleys) {
    TestData<unsigned char>()
        .setDimensions(6, 3)
        .setFeatureHeight(3)
        .setBackground(100)
        .setExpectedBackground(100)
        .drawSquare(1, 1, 1, 102)
        .drawExpectedSquare(1, 1, 1, 102)
        .drawSquare(3, 1, 1, 96)
        .drawExpectedSquare(3, 1, 1, 99)
        .drawSquare(5, 1, 1, 97)
        .drawSquare(1, 3, 1, 98)
        .drawSquare(3, 3, 1, 99)
        .drawSquare(5, 3, 1, 100);
}
