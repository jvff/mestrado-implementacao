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

TEST_F(MorphologicalReconstructionFilterTest, defaultSourceImageType) {
    using ImplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType>;
    using ExplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST_F(MorphologicalReconstructionFilterTest, sourceImageTypeIsPropagated) {
    using SourceImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;
    using ParentFilterClass = Filter<PixelType, PixelType, DestinationImageType,
            SourceImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

INSTANTIATE_TYPED_TEST_CASE_P(MorphologicalReconstructionFilterTest,
        MorphologicalReconstructionTests, TestData<unsigned char>);
