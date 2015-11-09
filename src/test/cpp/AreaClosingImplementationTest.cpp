#include "AreaClosingImplementationTest.hpp"

TEST_F(AreaClosingImplementationTest, classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST_F(AreaClosingImplementationTest, isFilterImplementation) {
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(AreaClosingImplementationTest, isConstructibleWithParameters) {
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const Image<SourcePixelType>&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationClass>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}
