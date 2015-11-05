#include "MorphologicalReconstructionImplementationTest.hpp"
#include "MorphologicalReconstructionTests.hpp"

TEST_F(MorphologicalReconstructionImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(MorphologicalReconstructionImplementationTest, isFilterImplementation) {
    using SubClass = DummyImplementationType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST_F(MorphologicalReconstructionImplementationTest, isConstructible) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementationType>::isConstructible(
            With<SourceImageParameter, DestinationImageParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(
        MorphologicalReconstructionImplementationTest,
        MorphologicalReconstructionTests, TestData);
