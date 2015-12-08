#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeLevelTest, classTemplateExists) {
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;

    AssertThat<DummyMaxTreeLevel>::isClassOrStruct();
}
