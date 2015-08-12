#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AdjustedMorphologicalGradientFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AdjustedMorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AdjustedMorphologicalGradientFilter<DummyType,
            DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
