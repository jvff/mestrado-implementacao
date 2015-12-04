#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeNodeTest, structTemplateExists) {
    AssertThat<MaxTreeNode<DummyType> >::isClassOrStruct();
}

TEST(MaxTreeNodeTest, hasDefaultConstructor) {
    AssertThat<MaxTreeNode<DummyType> >::isConstructible(WithoutParameters());
}

TEST(MaxTreeNodeTest, hasValueConstructor) {
    using ParentParameter = const std::shared_ptr<MaxTreeNode<DummyType> >&;
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<MaxTreeNode<DummyType> >::isConstructible(
            With<ParentParameter, LevelParameter, IdParameter>());
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

TEST(MaxTreeNodeTest, hasParentMember) {
    std::shared_ptr<MaxTreeNode<DummyType> > noParent;
    std::shared_ptr<MaxTreeNode<DummyType> > rootNode;

    DummyType parentLevel = { 90 };
    unsigned int parentId = 3;
    MaxTreeNode<DummyType> parent = { noParent, parentLevel, parentId };

    rootNode.reset(new MaxTreeNode<DummyType>(parent));

    DummyType childLevel = { 91 };
    unsigned int childId = 10;
    MaxTreeNode<DummyType> child = { rootNode, childLevel, childId };

    assertThat(child.level).isEqualTo(childLevel);
    assertThat(child.id).isEqualTo(childId);

    assertThat((bool)child.parent).isEqualTo(true);
    assertThat(child.parent->level).isEqualTo(parentLevel);
    assertThat(child.parent->id).isEqualTo(parentId);
    assertThat((bool)child.parent->parent).isEqualTo(false);
}
