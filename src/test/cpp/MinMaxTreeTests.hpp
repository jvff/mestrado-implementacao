#ifndef MIN_MAX_TREE_TESTS_HPP
#define MIN_MAX_TREE_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(MinMaxTreeTests);

COMPLEX_FILTER_TEST(allNodesAreAssignedToRootNode) {
    TestData<unsigned char>()
        .setDimensions(4, 2)
        .setColorsToUse({ 8 })
        .setBackground(0);
}

COMPLEX_FILTER_TEST(higherRegionIsAssignedToChildNode) {
    TestData<unsigned char>()
        .setDimensions(4, 4)
        .setColorsToUse({ 100, 200 })
        .setBackground(0)
        .drawSquare(1, 1, 2, 1);
}

COMPLEX_FILTER_TEST(twoRegionsAreAssignedToDifferentNodes) {
    TestData<unsigned char>()
        .setDimensions(7, 4)
        .setColorsToUse({ 100, 200 })
        .setBackground(0)
        .drawSquare(1, 1, 2, 1)
        .drawSquare(4, 1, 2, 1);
}

COMPLEX_FILTER_TEST(twoConnectedRegionsAreAssignedToSameNode) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setColorsToUse({ 200, 201, 205 })
        .setBackground(0)
        .drawSquare(1, 1, 2, 1)
        .drawSquareOnSameNode(1, 4, 2, 1)
        .drawSquare(2, 3, 1, 2);
}

COMPLEX_FILTER_TEST(twoConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setColorsToUse({ 200, 201, 202, 205 })
        .setBackground(0)
        .drawSquare(1, 1, 2, 1)
        .drawSquare(1, 4, 2, 2)
        .drawSquare(2, 3, 1, 3);
}

COMPLEX_FILTER_TEST(complexConnectedRegionsAreChained) {
    TestData<unsigned char>()
        .setDimensions(4, 7)
        .setColorsToUse({ 200, 201, 203, 205 })
        .setBackground(0)
        .drawSquare(1, 1, 2, 1)
        .drawSquareOnSameNode(1, 4, 2, 1)
        .drawSquare(2, 4, 1, 2)
        .drawSquare(2, 3, 1, 3);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(MinMaxTreeTests,
        allNodesAreAssignedToRootNode,
        higherRegionIsAssignedToChildNode,
        twoRegionsAreAssignedToDifferentNodes,
        twoConnectedRegionsAreAssignedToSameNode,
        twoConnectedRegionsAreChained,
        complexConnectedRegionsAreChained);

#endif
