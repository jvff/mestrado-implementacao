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
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getId()).isEqualTo(id);
}

TEST(MaxTreeNodeTest, hasSetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto newId = 761u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    node.setId(newId);

    assertThat(node.getId()).isEqualTo(newId);
}

TEST(MaxTreeNodeTest, hasGetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getLevel()).isEqualTo(level);
}

TEST(MaxTreeNodeTest, hasSetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto newLevel = DummyType{ 2485 };
    auto id = 15u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    node.setLevel(newLevel);

    assertThat(node.getLevel()).isEqualTo(newLevel);
}

TEST(MaxTreeNodeTest, hasParentMethodReturnsFalseForNewNode) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.hasParent()).isEqualTo(false);
}

TEST(MaxTreeNodeTest, hasParentMethodReturnsTreeForNewNodeWithParent) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    const auto childNode = MaxTreeNode<DummyType>(parentNode, childLevel,
            childId);

    assertThat(childNode.hasParent()).isEqualTo(true);
}

TEST(MaxTreeNodeTest, hasGetParentMethod) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    const auto childNode = MaxTreeNode<DummyType>(parentNode, childLevel,
            childId);

    auto& result = childNode.getParent();

    assertThat(result.getLevel()).isEqualTo(parentLevel);
    assertThat(result.getId()).isEqualTo(parentId);
}

TEST(MaxTreeNodeTest, getParentMethodReturnsConstReference) {
    auto level = DummyType{ 932 };
    auto id = 901u;
    const auto node = MaxTreeNode<DummyType>(level, id);

    AssertThat<decltype(node.getParent())>::isConstReference();
}

TEST(MaxTreeNodeTest, hasSetParentMethod) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;
    auto newParentLevel = DummyType{ 3 };
    auto newParentId = 784u;

    auto parentNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    auto childNode = MaxTreeNode<DummyType>(parentNode, childLevel, childId);
    auto newParentNode = std::make_shared<MaxTreeNode<DummyType> >(
            newParentLevel, newParentId);

    childNode.setParent(newParentNode);

    auto& result = childNode.getParent();

    assertThat(result.getLevel()).isEqualTo(newParentLevel);
    assertThat(result.getId()).isEqualTo(newParentId);
}

TEST(MaxTreeNodeTest, canBeConstructedWithoutParent) {
    DummyType level = { 4119 };
    unsigned int id = 109;

    auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getId()).isEqualTo(id);
    assertThat(node.getLevel()).isEqualTo(level);
    assertThat(node.hasParent()).isEqualTo(false);
}

TEST(MaxTreeNodeTest, hasParentMember) {
    auto parentLevel = DummyType{ 90 };
    auto parentId = 3u;

    auto childLevel = DummyType{ 91 };
    auto childId = 10u;

    auto rootNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);

    MaxTreeNode<DummyType> child = { rootNode, childLevel, childId };

    assertThat(child.getLevel()).isEqualTo(childLevel);
    assertThat(child.getId()).isEqualTo(childId);

    assertThat(child.hasParent()).isEqualTo(true);
    assertThat(child.getParent().getLevel()).isEqualTo(parentLevel);
    assertThat(child.getParent().getId()).isEqualTo(parentId);
    assertThat(child.getParent().hasParent()).isEqualTo(false);
}

TEST(MaxTreeNodeTest, copyConstructorCreatesDeepCopy) {
    auto parentLevel = DummyType{ 90 };
    auto parentId = 3u;

    auto childLevel = DummyType{ 91 };
    auto childId = 10u;

    auto rootNode = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);

    MaxTreeNode<DummyType> child = { rootNode, childLevel, childId };
    MaxTreeNode<DummyType> copy(child);

    assertThat(copy.getLevel()).isEqualTo(childLevel);
    assertThat(copy.getId()).isEqualTo(childId);

    assertThat(copy.hasParent()).isEqualTo(true);
    assertThat(copy.getParent()).isNotAtSameAddressAs(*rootNode);
    assertThat(copy.getParent().getLevel()).isEqualTo(parentLevel);
    assertThat(copy.getParent().getId()).isEqualTo(parentId);
    assertThat(copy.getParent().hasParent()).isEqualTo(false);
}
