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
