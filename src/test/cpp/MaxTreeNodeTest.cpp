#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeNodeTest, structTemplateExists) {
    AssertThat<MaxTreeNode<DummyType> >::isClassOrStruct();
}

TEST(MaxTreeNodeTest, hasValueMembers) {
    std::shared_ptr<MaxTreeNode<DummyType> > parent;
    DummyType level = { 7 };
    unsigned int id = 10;

    MaxTreeNode<DummyType> node = { parent, level, id };

    assertThat(node.id).isEqualTo(id);
    assertThat(node.level).isEqualTo(level);
    assertThat((bool)node.parent).isEqualTo(false);
}
