#include "MaxTreeNodeRemovalTest.hpp"

TEST_F(MaxTreeNodeRemovalTest, removingNodeUpdatesParentOfChildren) {
    tree.addNode(DummyType{ 20 });
    tree.addNode(DummyType{ 27 });
    tree.addNode(DummyType{ 33 });
    tree.addNode(DummyType{ 30 });
    tree.addNode(DummyType{ 30 });
    tree.removeNode(DummyType{ 27 }, 0u);

    verifyNodeChain(
            DummyType{ 30 }, 0u,
            DummyType{ 20 }, 0u);
    verifyNodeChain(
            DummyType{ 30 }, 1u,
            DummyType{ 20 }, 0u);
    verifyNodeChain(
            DummyType{ 33 }, 0u,
            DummyType{ 20 }, 0u);
}

TEST_F(MaxTreeNodeRemovalTest, correctNodeIsRemoved) {
    tree.addNode(DummyType{ 1 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 22 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 21 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 20 });

    tree.removeNode(DummyType{ 10 }, 1u);

    verifyNodeChain(
            DummyType{ 21 }, 0u,
            DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeNodeRemovalTest, cantRemoveFromInexistentLevels) {
    tree.addNode(DummyType{ 1 });
    tree.addNode(DummyType{ 3 });
    tree.removeNode(DummyType{ 0 }, 0u);
    tree.removeNode(DummyType{ 2 }, 0u);
    tree.removeNode(DummyType{ 4 }, 0u);

    verifyNodeChain(
            DummyType{ 3 }, 0u,
            DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeNodeRemovalTest, cantRemoveInexistentNode) {
    tree.addNode(DummyType{ 1 });
    tree.addNode(DummyType{ 3 });
    tree.addNode(DummyType{ 3 });
    tree.removeNode(DummyType{ 3 }, 2u);

    verifyNodeChain(
            DummyType{ 3 }, 0u,
            DummyType{ 1 }, 0u);
    verifyNodeChain(
            DummyType{ 3 }, 1u,
            DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeNodeRemovalTest, nodeIdsAreUpdatedAfterRemoval) {
    tree.addNode(DummyType{ 1 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 50 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 40 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 30 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 20 });

    tree.removeNode(DummyType{ 10 }, 1u);

    verifyNodeChain(
            DummyType{ 50 }, 0u,
            DummyType{ 10 }, 0u,
            DummyType{ 1 }, 0u);
    verifyNodeChain(
            DummyType{ 40 }, 0u,
            DummyType{ 1 }, 0u);
    verifyNodeChain(
            DummyType{ 30 }, 0u,
            DummyType{ 10 }, 1u,
            DummyType{ 1 }, 0u);
    verifyNodeChain(
            DummyType{ 20 }, 0u,
            DummyType{ 10 }, 2u,
            DummyType{ 1 }, 0u);
}