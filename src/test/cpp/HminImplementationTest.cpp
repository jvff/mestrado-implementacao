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
