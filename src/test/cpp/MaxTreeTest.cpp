#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTree.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeTest, classTemplateExists) {
    using DummyMaxTreeType = MaxTree<DummyType>;

    AssertThat<DummyMaxTreeType>::isClassOrStruct();
}
