#include "HmaxFilterTest.hpp"

TEST_F(HmaxFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(HmaxFilterTest, isFilter) {
    using FilterClass = HmaxFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilter>());
}

TEST_F(HmaxFilterTest, isConstructibleWithParameter) {
    using FeatureHeightParameter = const SourcePixelType&;

    AssertThat<DummyFilter>::isConstructible(With<FeatureHeightParameter>());
}

TEST_F(HmaxFilterTest, removesShallowHole) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(4)
        .setBackground(124)
        .drawSquare(1, 1, 5, 121)
        .setExpectedBackground(120);
}

TEST_F(HmaxFilterTest, doesntRemoveDeepHole) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(2)
        .setBackground(224)
        .drawSquare(1, 1, 5, 221)
        .setExpectedBackground(222)
        .drawExpectedSquare(1, 1, 5, 221);
}

TEST_F(HmaxFilterTest, shavesPeaks) {
    TestData<unsigned char>()
        .setDimensions(6, 3)
        .setFeatureHeight(3)
        .setBackground(10)
        .setExpectedBackground(10)
        .drawSquare(1, 1, 1, 9)
        .drawExpectedSquare(1, 1, 1, 9)
        .drawSquare(3, 1, 1, 14)
        .drawExpectedSquare(3, 1, 1, 11)
        .drawSquare(5, 1, 1, 13)
        .drawSquare(1, 3, 1, 12)
        .drawSquare(3, 3, 1, 11)
        .drawSquare(5, 3, 1, 10);
}
