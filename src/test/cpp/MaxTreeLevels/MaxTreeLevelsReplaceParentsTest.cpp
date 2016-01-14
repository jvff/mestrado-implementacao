#include "MaxTreeLevelsReplaceParentsTest.hpp"

TEST_F(MaxTreeLevelsReplaceParentsTest, nothingChangesWhenParentIsntFound) {
    auto inexistentLevel = makeNode(DummyType{ -1 }, 12u);
    auto newParent = makeNode(DummyType{ 0 }, 0u);

    createRootLevel(1);
    createLevelWithParents(2,
            1, 0,
            1, 0);
    createLevelWithParents(5,
            1, 0,
            2, 1,
            2, 0);

    levels.replaceParents(inexistentLevel, newParent);

    verifyTree(DummyType{ 1 },
            DummyType{ 2 },
                1, 0,
                1, 0,
            DummyType{ 5 },
                1, 0,
                2, 1,
                2, 0);
}

TEST_F(MaxTreeLevelsReplaceParentsTest, replacesOneParent) {
    createRootLevel(1);
    createLevelWithParents(2,
            1, 0,
            1, 0);
    createLevelWithParents(5,
            1, 0,
            2, 1,
            2, 0);

    auto oldParent = getNode(DummyType{ 2 }, 1u);
    auto newParent = getNode(DummyType{ 1 }, 0u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(DummyType{ 1 },
            DummyType{ 2 },
                1, 0,
                1, 0,
            DummyType{ 5 },
                1, 0,
                1, 0,
                2, 0);
}

TEST_F(MaxTreeLevelsReplaceParentsTest, replacesThreeParents) {
    createRootLevel(1);
    createLevelWithParents(2,
            1, 0,
            1, 0);
    createLevelWithParents(5,
            2, 0,
            1, 0,
            2, 1,
            2, 0,
            2, 0);

    auto oldParent = getNode(DummyType{ 2 }, 0u);
    auto newParent = getNode(DummyType{ 2 }, 1u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(DummyType{ 1 },
            DummyType{ 2 },
                1, 0,
                1, 0,
            DummyType{ 5 },
                2, 1,
                1, 0,
                2, 1,
                2, 1,
                2, 1);
}
