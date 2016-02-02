#include "MaxTreeNodeTest.hpp"

TEST_F(MaxTreeNodeTest, structTemplateExists) {
    AssertThat<MaxTreeNode<DummyType> >::isClassOrStruct();
}

TEST_F(MaxTreeNodeTest, hasDefaultConstructor) {
    AssertThat<MaxTreeNode<DummyType> >::isConstructible(WithoutParameters());
}

TEST_F(MaxTreeNodeTest, hasValueConstructor) {
    using ParentParameter = const std::shared_ptr<MaxTreeNode<DummyType> >&;
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<MaxTreeNode<DummyType> >::isConstructible(
            With<ParentParameter, LevelParameter, IdParameter>());
}

TEST_F(MaxTreeNodeTest, hasValueConstructorWithoutParent) {
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<MaxTreeNode<DummyType> >::isConstructible(
            With<LevelParameter, IdParameter>());
}

TEST_F(MaxTreeNodeTest, hasGetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getId()).isEqualTo(id);
}

TEST_F(MaxTreeNodeTest, hasSetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto newId = 761u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    node.setId(newId);

    assertThat(node.getId()).isEqualTo(newId);
}

TEST_F(MaxTreeNodeTest, hasGetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getLevel()).isEqualTo(level);
}

TEST_F(MaxTreeNodeTest, hasSetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto newLevel = DummyType{ 2485 };
    auto id = 15u;
    auto node = MaxTreeNode<DummyType>{ level, id };

    node.setLevel(newLevel);

    assertThat(node.getLevel()).isEqualTo(newLevel);
}

TEST_F(MaxTreeNodeTest, hasParentMethodReturnsFalseForNewNode) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.hasParent()).isEqualTo(false);
}

TEST_F(MaxTreeNodeTest, hasParentMethodReturnsTreeForNewNodeWithParent) {
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

TEST_F(MaxTreeNodeTest, hasGetParentMethod) {
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

TEST_F(MaxTreeNodeTest, getParentMethodReturnsConstReference) {
    auto level = DummyType{ 932 };
    auto id = 901u;
    const auto node = MaxTreeNode<DummyType>(level, id);

    AssertThat<decltype(node.getParent())>::isConstReference();
}

TEST_F(MaxTreeNodeTest, hasSetParentMethod) {
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

TEST_F(MaxTreeNodeTest, canBeConstructedWithoutParent) {
    DummyType level = { 4119 };
    unsigned int id = 109;

    auto node = MaxTreeNode<DummyType>{ level, id };

    assertThat(node.getId()).isEqualTo(id);
    assertThat(node.getLevel()).isEqualTo(level);
    assertThat(node.hasParent()).isEqualTo(false);
}

TEST_F(MaxTreeNodeTest, canBeConstructedWithParent) {
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
