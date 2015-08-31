#include "MorphologicalReconstructionImplementationTest.hpp"

TEST_F(MorphologicalReconstructionImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(MorphologicalReconstructionImplementationTest, isFilterImplementation) {
    using SubClass = DummyImplementationType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}
