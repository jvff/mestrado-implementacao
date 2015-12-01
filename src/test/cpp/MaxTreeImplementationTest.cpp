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

TEST_F(MaxTreeImplementationTest, twoRegionsAreAssignedToDifferentNodes) {
    TestData<unsigned char>()
        .setDimensions(7, 4)
        .setBackground(100)
        .drawSquare(1, 1, 2, 200)
        .drawSquare(4, 1, 2, 200);
}

TEST_F(MaxTreeImplementationTest, twoConnectedRegionsAreAssignedToSameNode) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquareOnSameNode(1, 4, 2, 201)
        .drawSquare(2, 3, 1, 205);
}

TEST_F(MaxTreeImplementationTest, twoConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquare(1, 4, 2, 202)
        .drawSquare(2, 3, 1, 205);
}

TEST_F(MaxTreeImplementationTest, complexConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquareOnSameNode(1, 4, 2, 201)
        .drawSquare(2, 4, 1, 203)
        .drawSquare(2, 3, 1, 205);
}
