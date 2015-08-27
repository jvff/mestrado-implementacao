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
