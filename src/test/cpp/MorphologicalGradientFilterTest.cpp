#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalGradientFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
