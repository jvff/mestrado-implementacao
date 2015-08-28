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

TEST_F(ComplexFilterTest, applyMethodUsesImplementation) {
    FakeDummyFilterType filter;
    Mock<FakeDummyFilterType> filterSpy(filter);

    auto sourceImageMock = createSourceImageMock(101, 43);
    auto destinationImageMock = createDestinationImageMock(79, 97);
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    ImplementationType implementation(sourceImage, destinationImage);
    auto& implementationSpy = implementation.getSpy();

    When(Method(implementationSpy, apply)).Return();
    When(Method(filterSpy, instantiateImplementation))
        .Return(std::ref(implementation));

    filter.apply(sourceImage, destinationImage);

    Verify(Method(filterSpy, instantiateImplementation)
            +  Method(implementationSpy, apply));
}
