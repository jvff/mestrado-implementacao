#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeLevelTest, classTemplateExists) {
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;

    AssertThat<DummyMaxTreeLevel>::isClassOrStruct();
}

TEST(MaxTreeLevelTest, isConstructibleWithLevelParameter) {
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;
    using LevelParameter = const DummyType&;

    AssertThat<DummyMaxTreeLevel>::isConstructible(With<LevelParameter>());
}

TEST(MaxTreeLevelTest, isInitiallyEmpty) {
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;

    DummyMaxTreeLevel level(DummyType{ 201 });

    assertThat(level.isEmpty()).isEqualTo(true);
}
