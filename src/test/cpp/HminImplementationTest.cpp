#include "HminImplementationTest.hpp"

TEST_F(HminImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(HminImplementationTest, isFilterImplementation) {
    using ImplementationClass = HminImplementation<SourceImageType,
            DestinationImageType>;
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}
