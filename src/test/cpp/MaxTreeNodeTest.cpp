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

TEST(MaxTreeNodeTest, hasValueConstructorWithoutParent) {
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<MaxTreeNode<DummyType> >::isConstructible(
            With<LevelParameter, IdParameter>());
}

TEST(MaxTreeNodeTest, hasGetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getId()).isEqualTo(id);
}

TEST(MaxTreeNodeTest, hasGetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getLevel()).isEqualTo(level);
}

TEST(MaxTreeNodeTest, hasGetParentMethod) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    auto childNode = MaxTreeNode<DummyType>(parentNode, childLevel, childId);

    auto result = childNode.getParent();

    assertThat(result.getLevel()).isEqualTo(parentLevel);
    assertThat(result.getId()).isEqualTo(parentId);
}

TEST(MaxTreeNodeTest, hasValueMembers) {
    std::shared_ptr<MaxTreeNode<DummyType> > parent;
    DummyType level = { 7 };
    unsigned int id = 10;

    auto node = MaxTreeNode<DummyType>{ parent, level, id };

    assertThat(node.id).isEqualTo(id);
    assertThat(node.level).isEqualTo(level);
    assertThat((bool)node.parent).isEqualTo(false);
}

TEST(MaxTreeNodeTest, canBeConstructedWithoutParent) {
    DummyType level = { 4119 };
    unsigned int id = 109;

    auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.id).isEqualTo(id);
    assertThat(node.level).isEqualTo(level);
    assertThat((bool)node.parent).isEqualTo(false);
}

TEST(MaxTreeNodeTest, hasParentMember) {
    auto rootNode = std::make_shared<MaxTreeNode<DummyType> >();

    auto parentLevel = DummyType{ 90 };
    auto parentId = 3u;

    auto childLevel = DummyType{ 91 };
    auto childId = 10u;

    rootNode->level = parentLevel;
    rootNode->id = parentId;

    MaxTreeNode<DummyType> child = { rootNode, childLevel, childId };

    assertThat(child.level).isEqualTo(childLevel);
    assertThat(child.id).isEqualTo(childId);

    assertThat((bool)child.parent).isEqualTo(true);
    assertThat(child.parent->level).isEqualTo(parentLevel);
    assertThat(child.parent->id).isEqualTo(parentId);
    assertThat((bool)child.parent->parent).isEqualTo(false);
}

TEST(MaxTreeNodeTest, copyConstructorCreatesDeepCopy) {
    auto rootNode = std::make_shared<MaxTreeNode<DummyType> >();

    auto parentLevel = DummyType{ 90 };
    auto parentId = 3u;

    auto childLevel = DummyType{ 91 };
    auto childId = 10u;

    rootNode->level = parentLevel;
    rootNode->id = parentId;

    MaxTreeNode<DummyType> child = { rootNode, childLevel, childId };
    MaxTreeNode<DummyType> copy(child);

    assertThat(copy.level).isEqualTo(childLevel);
    assertThat(copy.id).isEqualTo(childId);

    assertThat((bool)copy.parent).isEqualTo(true);
    assertThat(copy.parent).isNotEqualTo(rootNode);
    assertThat(copy.parent->level).isEqualTo(parentLevel);
    assertThat(copy.parent->id).isEqualTo(parentId);
    assertThat((bool)copy.parent->parent).isEqualTo(false);
}
