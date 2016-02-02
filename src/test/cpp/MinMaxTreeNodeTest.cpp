#include "MinMaxTreeNodeTest.hpp"

using NodeTypes = ::testing::Types<MaxTreeNode<DummyType>,
        MinTreeNode<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeNodeTest, NodeTypes);

MIN_MAX_TREE_NODE_TEST(structTemplateExists) {
    AssertThat<NodeType>::isClassOrStruct();
}

MIN_MAX_TREE_NODE_TEST(hasDefaultConstructor) {
    AssertThat<NodeType>::isConstructible(WithoutParameters());
}

MIN_MAX_TREE_NODE_TEST(hasValueConstructor) {
    using ParentParameter = const std::shared_ptr<NodeType>&;
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<NodeType>::isConstructible(With<ParentParameter, LevelParameter,
            IdParameter>());
}

MIN_MAX_TREE_NODE_TEST(hasValueConstructorWithoutParent) {
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<NodeType>::isConstructible(With<LevelParameter, IdParameter>());
}

MIN_MAX_TREE_NODE_TEST(hasGetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.getId()).isEqualTo(id);
}

MIN_MAX_TREE_NODE_TEST(hasSetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto newId = 761u;
    auto node = NodeType{ level, id };

    node.setId(newId);

    assertThat(node.getId()).isEqualTo(newId);
}

MIN_MAX_TREE_NODE_TEST(hasGetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.getLevel()).isEqualTo(level);
}

MIN_MAX_TREE_NODE_TEST(hasSetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto newLevel = DummyType{ 2485 };
    auto id = 15u;
    auto node = NodeType{ level, id };

    node.setLevel(newLevel);

    assertThat(node.getLevel()).isEqualTo(newLevel);
}

MIN_MAX_TREE_NODE_TEST(hasParentMethodReturnsFalseForNewNode) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.hasParent()).isEqualTo(false);
}

MIN_MAX_TREE_NODE_TEST(hasParentMethodReturnsTreeForNewNodeWithParent) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<NodeType>(parentLevel, parentId);
    const auto childNode = NodeType(parentNode, childLevel, childId);

    assertThat(childNode.hasParent()).isEqualTo(true);
}

MIN_MAX_TREE_NODE_TEST(hasGetParentMethod) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<NodeType>(parentLevel, parentId);
    const auto childNode = NodeType(parentNode, childLevel, childId);

    auto& result = childNode.getParent();

    assertThat(result.getLevel()).isEqualTo(parentLevel);
    assertThat(result.getId()).isEqualTo(parentId);
}

MIN_MAX_TREE_NODE_TEST(getParentMethodReturnsConstReference) {
    auto level = DummyType{ 932 };
    auto id = 901u;
    const auto node = NodeType(level, id);

    AssertThat<decltype(node.getParent())>::isConstReference();
}

MIN_MAX_TREE_NODE_TEST(hasSetParentMethod) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;
    auto newParentLevel = DummyType{ 3 };
    auto newParentId = 784u;

    auto parentNode = std::make_shared<NodeType>(parentLevel, parentId);
    auto childNode = NodeType(parentNode, childLevel, childId);
    auto newParentNode = std::make_shared<NodeType>(newParentLevel,
            newParentId);

    childNode.setParent(newParentNode);

    auto& result = childNode.getParent();

    assertThat(result.getLevel()).isEqualTo(newParentLevel);
    assertThat(result.getId()).isEqualTo(newParentId);
}

MIN_MAX_TREE_NODE_TEST(canBeConstructedWithoutParent) {
    DummyType level = { 4119 };
    unsigned int id = 109;

    auto node = NodeType{ level, id };

    assertThat(node.getId()).isEqualTo(id);
    assertThat(node.getLevel()).isEqualTo(level);
    assertThat(node.hasParent()).isEqualTo(false);
}

MIN_MAX_TREE_NODE_TEST(canBeConstructedWithParent) {
    auto parentLevel = DummyType{ 90 };
    auto parentId = 3u;

    auto childLevel = DummyType{ 91 };
    auto childId = 10u;

    auto rootNode = std::make_shared<NodeType>(parentLevel, parentId);

    NodeType child = { rootNode, childLevel, childId };

    assertThat(child.getLevel()).isEqualTo(childLevel);
    assertThat(child.getId()).isEqualTo(childId);
    assertThat(child.hasParent()).isEqualTo(true);

    assertThat(child.getParent().getLevel()).isEqualTo(parentLevel);
    assertThat(child.getParent().getId()).isEqualTo(parentId);
    assertThat(child.getParent().hasParent()).isEqualTo(false);
}
