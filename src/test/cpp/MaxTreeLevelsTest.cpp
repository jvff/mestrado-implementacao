#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevels.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeLevelsTest, classTemplateExists) {
    using DummyMaxTreeLevels = MaxTreeLevels<DummyType>;

    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}
