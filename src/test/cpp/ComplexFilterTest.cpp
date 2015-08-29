#include "ComplexFilterTest.hpp"
#include "FakeInstantiatingComplexFilter.hpp"

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

TEST_F(ComplexFilterTest, doesntInstantiateImplementationWithParameters) {
    using ConstructorParameter = DummyType;
    using ImplementationType =
            FakeFilterImplementationWithConstructorParameters<SourceImageType,
                    DestinationImageType, ConstructorParameter>;
    using FilterType = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<FilterType>::isNotConstructible(WithoutParameters());
}

TEST_F(ComplexFilterTest, applyMethodUsesImplementationWithParameters) {
    using FirstParameterType = DummyTypes<3>;
    using SecondParameterType = DummyTypes<4>;
    using ImplementationType = SpiedFakeFilterImplementation<SourceImageType,
            DestinationImageType,
            FakeFilterImplementationWithConstructorParameters,
            FirstParameterType, SecondParameterType>;
    using FilterType = FakeInstantiatingComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType, FirstParameterType,
            SecondParameterType>;

    FirstParameterType firstParameter;
    SecondParameterType secondParameter;

    FilterType filter(firstParameter, secondParameter);
    Mock<FilterType> filterSpy(filter);

    auto sourceImageMock = createSourceImageMock(1022, 877);
    auto destinationImageMock = createDestinationImageMock(10, 11);
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    ImplementationType implementation(sourceImage, destinationImage,
            firstParameter, secondParameter);
    auto& implementationSpy = implementation.getSpy();

    When(Method(implementationSpy, apply)).Return();
    When(Method(filterSpy, instantiateImplementation))
        .Return(std::ref(implementation));

    filter.apply(sourceImage, destinationImage);

    Verify(Method(filterSpy, instantiateImplementation)
            +  Method(implementationSpy, apply));
}
