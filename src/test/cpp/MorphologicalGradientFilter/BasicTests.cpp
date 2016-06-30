#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MorphologicalGradientFilter.hpp"
#include "SimpleFilter.hpp"

#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

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
