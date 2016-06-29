#include "MorphologicalGradientFilterTest.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalGradientFilterTestData<PixelType, ImageType>;

TEST(MorphologicalGradientFilterTest, classTemplateExists) {
    using SourceImageType = Image<DummyType>;
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(MorphologicalGradientFilterTest, isSimpleFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = MorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;
    using SuperClass = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(MorphologicalGradientFilterTest, isConstructibleWithParameter) {
    using SourceImageType = Image<DummyType>;
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;
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
