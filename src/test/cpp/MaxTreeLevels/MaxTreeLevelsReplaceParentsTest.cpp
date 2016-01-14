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

TEST_F(MaxTreeLevelsReplaceParentsTest, replacesParentsOnDifferentLevels) {
    createRootLevel(1);
    createLevelWithParents(2,
            1, 0,
            1, 0,
            1, 0);
    createLevelWithParents(5,
            2, 0,
            1, 0,
            2, 1,
            2, 0,
            2, 2);
    createLevelWithParents(6,
            2, 2,
            5, 1,
            5, 4,
            2, 0,
            5, 2);
    createLevelWithParents(10,
            6, 0,
            6, 3,
            5, 4,
            2, 2,
            2, 0,
            5, 0);
    createLevelWithParents(11,
            10, 0,
            5, 1,
            10, 3,
            5, 1,
            10, 2,
            6, 3);

    auto oldParent = getNode(DummyType{ 5 }, 1u);
    auto newParent = getNode(DummyType{ 2 }, 2u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(DummyType{ 1 },
            DummyType{ 2 },
                1, 0,
                1, 0,
                1, 0,
            DummyType{ 5 },
                2, 0,
                1, 0,
                2, 1,
                2, 0,
                2, 2,
            DummyType{ 6 },
                2, 2,
                2, 2,
                5, 4,
                2, 0,
                5, 2,
            DummyType{ 10 },
                6, 0,
                6, 3,
                5, 4,
                2, 2,
                2, 0,
                5, 0,
            DummyType{ 11 },
                10, 0,
                2, 2,
                10, 3,
                2, 2,
                10, 2,
                6, 3);
}
