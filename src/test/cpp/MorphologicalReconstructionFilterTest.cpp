#include "MorphologicalReconstructionFilterTest.hpp"
#include "MorphologicalReconstructionTests.hpp"

TEST(MorphologicalReconstructionFilterTest, classIsntAbstract) {
    using PixelType = DummyType;
    using ImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType, ImageType>;

    AssertThat<FilterClass>::isConstructible(WithoutParameters());
}

TEST(MorphologicalReconstructionFilterTest, isComplexFilter) {
    using PixelType = DummyType;
    using SourceImageType = Image<PixelType>;
    using DestinationImageType = FakeImage<PixelType>;
    using ImplementationType = MorphologicalReconstructionImplementation<
            SourceImageType, DestinationImageType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;
    using ParentFilterClass = ComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

TEST(MorphologicalReconstructionFilterTest, defaultSourceImageType) {
    using PixelType = DummyType;
    using DestinationImageType = FakeImage<PixelType>;
    using SourceImageType = Image<PixelType>;
    using ImplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType>;
    using ExplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(MorphologicalReconstructionFilterTest, sourceImageTypeIsPropagated) {
    using PixelType = DummyType;
    using DestinationImageType = FakeImage<PixelType>;
    using SourceImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;
    using ParentFilterClass = Filter<PixelType, PixelType, DestinationImageType,
            SourceImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

INSTANTIATE_TYPED_TEST_CASE_P(MorphologicalReconstructionFilterTest,
        MorphologicalReconstructionTests, TestData<unsigned char>);
