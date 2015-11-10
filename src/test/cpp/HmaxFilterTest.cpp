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
