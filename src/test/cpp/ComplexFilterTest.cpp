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
    setUpSourceImageMock(101, 43);
    setUpDestinationImageSpy(79, 97);

    auto result = filter.instantiateImplementation(sourceImage,
            *destinationImagePtr);

    auto& storedSourceImage = result.getSourceImage();
    auto& storedDestinationImage = result.getDestinationImage();

    assertThat(storedSourceImage).isAtSameAddressAs(sourceImage);
    assertThat(storedDestinationImage).isAtSameAddressAs(*destinationImagePtr);
}

TEST_F(ComplexFilterTest, applyMethodUsesImplementation) {
    setUpSourceImageMock(101, 43);
    setUpDestinationImageSpy(79, 97);

    auto& implementationSpy = setUpImplementationSpy();

    mockInstantiation();

    filter.apply(sourceImage, *destinationImagePtr);

    Verify(Method(filterSpy, instantiateImplementation)
            +  Method(implementationSpy, apply));
}

TEST_F(ComplexFilterTest, applyMethodCallsApplyMethodWithDestinationImage) {
    using ApplyMethodSignature = void(const SourceImageType&,
            DestinationImageType&);

    unsigned int width = 890;
    unsigned int height = 234;

    setUpSourceImageMock(239, 252);
    setUpDestinationImageSpy(width, height);

    auto& implementationSpy = setUpImplementationSpy();

    mockInstantiation();

    When(Method(filterSpy, createDestinationImage))
        .Return(*destinationImagePtr);
    Spy(OverloadedMethod(filterSpy, apply, ApplyMethodSignature));

    auto result = filter.apply(sourceImage);

    Verify(OverloadedMethod(filterSpy, apply, ApplyMethodSignature)
            + Method(filterSpy, instantiateImplementation)
            + Method(implementationSpy, apply));

    assertThat(result.getWidth()).isEqualTo(width);
    assertThat(result.getHeight()).isEqualTo(height);
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

    setUpSourceImageMock(1022, 877);
    setUpDestinationImageSpy(10, 11);

    auto implementation = ImplementationType(sourceImage, *destinationImagePtr,
            firstParameter, secondParameter);
    auto& implementationSpy = implementation.getSpy();

    When(Method(implementationSpy, apply)).Return();
    When(Method(filterSpy, instantiateImplementation))
        .Return(std::ref(implementation));

    filter.apply(sourceImage, *destinationImagePtr);

    Verify(Method(filterSpy, instantiateImplementation)
            +  Method(implementationSpy, apply));
}
