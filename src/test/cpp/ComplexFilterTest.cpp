#include "ComplexFilterTest.hpp"

TEST_F(ComplexFilterTest, classTemplateExists) {
    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST_F(ComplexFilterTest, isSubClassOfFilter) {
    using SubClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST_F(ComplexFilterTest, hasMethodToInstatiateImplementation) {
    FakeDummyFilterType filter;

    auto sourceImageMock = createSourceImageMock(101, 43);
    auto destinationImageMock = createDestinationImageMock(79, 97);
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    auto result = filter.instantiateImplementation(sourceImage,
            destinationImage);

    auto& storedSourceImage = result.getSourceImage();
    auto& storedDestinationImage = result.getDestinationImage();

    assertThat(storedSourceImage).isAtSameAddressAs(sourceImage);
    assertThat(storedDestinationImage).isAtSameAddressAs(destinationImage);
}
