#include "MorphologicalReconstructionFilterTest.hpp"
#include "MorphologicalReconstructionTests.hpp"

TEST_F(MorphologicalReconstructionFilterTest, classIsntAbstract) {
    AssertThat<DummyFilterType>::isConstructible(WithoutParameters());
}

TEST_F(MorphologicalReconstructionFilterTest, isComplexFilter) {
    using FilterClass = DummyFilterType;
    using ParentFilterClass = ComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MorphologicalReconstructionFilterTest,
        MorphologicalReconstructionTests, TestData);
