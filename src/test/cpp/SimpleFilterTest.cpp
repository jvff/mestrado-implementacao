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

TEST_F(SimpleFilterTest, applyWithDestinationImageCallsPerPixelApplyMethod) {
    using FilterType = FakeSimpleFilter<SourceImageType, DestinationImageType>;
    using MethodSignature = DestinationPixelType(unsigned int, unsigned int,
            const SourceImageType&);

    unsigned int width = 10;
    unsigned int height = 8;

    FilterType filter;
    Mock<FilterType> spy(filter);

    Spy(OverloadedMethod(spy, apply, MethodSignature));

    auto sourceImageMock = createSourceImageMock(width, height);
    const auto& sourceImage = sourceImageMock.get();
    auto destinationImage = DestinationImageType(width, height);

    filter.apply(sourceImage, destinationImage);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            Verify(OverloadedMethod(spy, apply, MethodSignature)
                    .Using(x, y, RefTo(sourceImage)));
        }
    }
}
