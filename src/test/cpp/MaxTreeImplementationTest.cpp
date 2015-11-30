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
    TestData<unsigned char>()
        .setDimensions(4, 2)
        .setBackground(8);
}

TEST_F(MaxTreeImplementationTest, higherRegionIsAssignedToChildNode) {
    TestData<unsigned char>()
        .setDimensions(4, 4)
        .setBackground(100)
        .drawSquare(1, 1, 2, 200);
}
