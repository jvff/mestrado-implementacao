#include "SimpleFilterTest.hpp"

TEST_F(SimpleFilterTest, classTemplateExists) {
    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST_F(SimpleFilterTest, isSubClassOfFilter) {
    using SubClass = SimpleFilter<SourceImageType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST_F(SimpleFilterTest, destinationDimensionsAreSameAsSourceDimensions) {
    using FilterType = FakeSimpleFilter<SourceImageType, DestinationImageType>;

    unsigned int width = 10;
    unsigned int height = 8;

    FilterType filter;

    auto sourceImageMock = createSourceImageMock(width, height);
    const auto& sourceImage = sourceImageMock.get();

    auto result = filter.apply(sourceImage);

    assertThat(result.getWidth()).isEqualTo(width);
    assertThat(result.getHeight()).isEqualTo(height);
}
