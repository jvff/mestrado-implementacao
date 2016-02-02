#include "MinMaxTreeNodeTest.hpp"

using NodeTypes = ::testing::Types<MaxTreeNode<DummyType>,
        MinTreeNode<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeNodeTest, NodeTypes);

TEST_C(structTemplateExists) {
    AssertThat<NodeType>::isClassOrStruct();
}

TEST_C(hasDefaultConstructor) {
    AssertThat<NodeType>::isConstructible(WithoutParameters());
}

TEST_C(hasValueConstructor) {
    using ParentParameter = const std::shared_ptr<NodeType>&;
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<NodeType>::isConstructible(With<ParentParameter, LevelParameter,
            IdParameter>());
}

TEST_C(hasValueConstructorWithoutParent) {
    using LevelParameter = const DummyType&;
    using IdParameter = unsigned int;

    AssertThat<NodeType>::isConstructible(With<LevelParameter, IdParameter>());
}

TEST_C(hasGetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.getId()).isEqualTo(id);
}

TEST_C(hasSetIdMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    auto newId = 761u;
    auto node = NodeType{ level, id };

    node.setId(newId);

    assertThat(node.getId()).isEqualTo(newId);
}

TEST_C(hasGetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.getLevel()).isEqualTo(level);
}

TEST_C(hasSetLevelMethod) {
    auto level = DummyType{ 1390 };
    auto newLevel = DummyType{ 2485 };
    auto id = 15u;
    auto node = NodeType{ level, id };

    node.setLevel(newLevel);

    assertThat(node.getLevel()).isEqualTo(newLevel);
}

TEST_C(hasParentMethodReturnsFalseForNewNode) {
    auto level = DummyType{ 1390 };
    auto id = 15u;
    const auto node = NodeType{ level, id };

    assertThat(node.hasParent()).isEqualTo(false);
}

TEST_C(hasParentMethodReturnsTreeForNewNodeWithParent) {
    auto parentLevel = DummyType{ 6178 };
    auto parentId = 21u;
    auto childLevel = DummyType{ 10401 };
    auto childId = 30u;

    auto parentNode = std::make_shared<NodeType>(parentLevel, parentId);
    const auto childNode = NodeType(parentNode, childLevel, childId);

    assertThat(childNode.hasParent()).isEqualTo(true);
}

TEST_C(hasGetParentMethod) {
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

TEST_C(getParentMethodReturnsConstReference) {
    auto level = DummyType{ 932 };
    auto id = 901u;
    const auto node = NodeType(level, id);

    AssertThat<decltype(node.getParent())>::isConstReference();
}

TEST_C(hasSetParentMethod) {
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

TEST_C(canBeConstructedWithoutParent) {
    DummyType level = { 4119 };
    unsigned int id = 109;

    auto node = NodeType{ level, id };

    assertThat(node.getId()).isEqualTo(id);
    assertThat(node.getLevel()).isEqualTo(level);
    assertThat(node.hasParent()).isEqualTo(false);
}

TEST_C(canBeConstructedWithParent) {
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
