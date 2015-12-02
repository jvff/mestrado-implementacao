#ifndef MAX_TREE_TESTS_HPP
#define MAX_TREE_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(MaxTreeTests);

COMPLEX_FILTER_TEST(allNodesAreAssignedToRootNode) {
    TestData<unsigned char>()
        .setDimensions(4, 2)
        .setBackground(8);
}

COMPLEX_FILTER_TEST(higherRegionIsAssignedToChildNode) {
    TestData<unsigned char>()
        .setDimensions(4, 4)
        .setBackground(100)
        .drawSquare(1, 1, 2, 200);
}

COMPLEX_FILTER_TEST(twoRegionsAreAssignedToDifferentNodes) {
    TestData<unsigned char>()
        .setDimensions(7, 4)
        .setBackground(100)
        .drawSquare(1, 1, 2, 200)
        .drawSquare(4, 1, 2, 200);
}

COMPLEX_FILTER_TEST(twoConnectedRegionsAreAssignedToSameNode) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquareOnSameNode(1, 4, 2, 201)
        .drawSquare(2, 3, 1, 205);
}

COMPLEX_FILTER_TEST(twoConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquare(1, 4, 2, 202)
        .drawSquare(2, 3, 1, 205);
}

COMPLEX_FILTER_TEST(complexConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setBackground(200)
        .drawSquare(1, 1, 2, 201)
        .drawSquareOnSameNode(1, 4, 2, 201)
        .drawSquare(2, 4, 1, 203)
        .drawSquare(2, 3, 1, 205);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(MaxTreeTests, allNodesAreAssignedToRootNode,
        higherRegionIsAssignedToChildNode,
        twoRegionsAreAssignedToDifferentNodes,
        twoConnectedRegionsAreAssignedToSameNode,
        twoConnectedRegionsAreChained,
        complexConnectedRegionsAreChained);

#endif
