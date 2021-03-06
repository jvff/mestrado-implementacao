#include "AdjustedMorphologicalGradientFilterTest.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AdjustedMorphologicalGradientFilterTestData<PixelType,
        ImageType>;

TEST(AdjustedMorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AdjustedMorphologicalGradientFilter<Image<DummyType>,
            ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AdjustedMorphologicalGradientFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = AdjustedMorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(AdjustedMorphologicalGradientFilterTest, isConstructibleWithParameters) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AdjustedMorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;
    using StructureSizeParameter = unsigned int;
    using ThresholdParameter = const SourcePixelType&;
    using MaxPixelValueParameter = const DestinationPixelType&;
    using AdjustmentExponentParameter = float;

    AssertThat<DummyFilter>::isConstructible(With<StructureSizeParameter,
            ThresholdParameter, MaxPixelValueParameter,
            AdjustmentExponentParameter>());
}

TEST(AdjustedMorphologicalGradientFilterTest, lightSquare) {
    TestData<unsigned char>()
        .setDimensions(10, 10)
        .setStructureSize(1)
        .setActivationThreshold(1)
        .setMaxPixelValue(0xFF)
        .setAdjustmentExponent(0.01)
        .setBackground(50)
        .drawSquare(2, 2, 6, 100);
}

TEST(AdjustedMorphologicalGradientFilterTest, darkSquare) {
    TestData<unsigned char>()
        .setDimensions(10, 10)
        .setStructureSize(1)
        .setActivationThreshold(200)
        .setMaxPixelValue(0xFF)
        .setAdjustmentExponent(0.01)
        .setBackground(50)
        .drawSquare(2, 2, 6, 100);
}

TEST(AdjustedMorphologicalGradientFilterTest, lightSquareAndDarkSquare) {
    TestData<unsigned char>()
        .setDimensions(18, 10)
        .setStructureSize(1)
        .setActivationThreshold(100)
        .setMaxPixelValue(0xFF)
        .setAdjustmentExponent(0.1)
        .setBackground(25)
        .drawSquare(2, 2, 6, 150)
        .drawSquare(10, 2, 6, 50);
}
