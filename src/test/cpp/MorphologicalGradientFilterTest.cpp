#include "MorphologicalGradientFilterTest.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalGradientFilterTestData<PixelType, ImageType>;

TEST(MorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(MorphologicalGradientFilterTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(MorphologicalGradientFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(MorphologicalGradientFilterTest, isConstructibleWithParameter) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<DummyType, DummyType,
            ImageType>;
    using StructureSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<StructureSizeParameter>());
}

TEST(MorphologicalGradientFilterTest, binarySquare) {
    TestData<bool>()
        .setDimensions(10, 10)
        .setStructureSize(1)
        .setBackground(false)
        .drawSquare(2, 2, 6, true);
}

TEST(MorphologicalGradientFilterTest, grayscaleSquare) {
    TestData<unsigned char>()
        .setDimensions(10, 10)
        .setStructureSize(2)
        .setBackground(20)
        .drawSquare(2, 2, 6, 27);
}

TEST(MorphologicalGradientFilterTest, twoGrayscaleSquares) {
    TestData<unsigned char>()
        .setDimensions(23, 15)
        .setStructureSize(3)
        .setBackground(100)
        .drawSquare(4, 4, 7, 101)
        .drawSquare(12, 4, 7, 102);
}

TEST(MorphologicalGradientFilterTest, threeGrayscaleSquares) {
    TestData<unsigned char>()
        .setDimensions(23, 15)
        .setStructureSize(1)
        .setBackground(100)
        .drawSquare(4, 4, 7, 101)
        .drawSquare(12, 4, 7, 102)
        .drawSquare(10, 6, 3, 109);
}