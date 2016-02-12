#include "ReplaceParentsTest.hpp"

TEST_C(ReplaceParentsTest, nothingChangesWhenParentIsntFound) {
    auto levelHeights = makeLevelHeights({1, 2, 5});
    auto inexistentLevel = makeNode(DummyType{ -1 }, 12u);
    auto newParent = makeNode(DummyType{ 0 }, 0u);

    createRootLevel(levelHeights[0]);
    createLevelWithParents(levelHeights[1],
            levelHeights[0], 0,
            levelHeights[0], 0);
    createLevelWithParents(levelHeights[2],
            levelHeights[0], 0,
            levelHeights[1], 1,
            levelHeights[1], 0);

    levels.replaceParents(inexistentLevel, newParent);

    verifyTree(levelHeights[0],
            levelHeights[1],
                levelHeights[0], 0,
                levelHeights[0], 0,
            levelHeights[2],
                levelHeights[0], 0,
                levelHeights[1], 1,
                levelHeights[1], 0);
}

TEST_C(ReplaceParentsTest, replacesOneParent) {
    auto levelHeights = makeLevelHeights({ 1, 2, 5 });

    createRootLevel(levelHeights[0]);
    createLevelWithParents(levelHeights[1],
            levelHeights[0], 0,
            levelHeights[0], 0);
    createLevelWithParents(levelHeights[2],
            levelHeights[0], 0,
            levelHeights[1], 1,
            levelHeights[1], 0);

    auto oldParent = getNode(levelHeights[1], 1u);
    auto newParent = getNode(levelHeights[0], 0u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(levelHeights[0],
            levelHeights[1],
                levelHeights[0], 0,
                levelHeights[0], 0,
            levelHeights[2],
                levelHeights[0], 0,
                levelHeights[0], 0,
                levelHeights[1], 0);
}

TEST_C(ReplaceParentsTest, replacesThreeParents) {
    auto levelHeights = makeLevelHeights({ 1, 2, 5 });

    createRootLevel(levelHeights[0]);
    createLevelWithParents(levelHeights[1],
            levelHeights[0], 0,
            levelHeights[0], 0);
    createLevelWithParents(levelHeights[2],
            levelHeights[1], 0,
            levelHeights[0], 0,
            levelHeights[1], 1,
            levelHeights[1], 0,
            levelHeights[1], 0);

    auto oldParent = getNode(levelHeights[1], 0u);
    auto newParent = getNode(levelHeights[1], 1u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(levelHeights[0],
            levelHeights[1],
                levelHeights[0], 0,
                levelHeights[0], 0,
            levelHeights[2],
                levelHeights[1], 1,
                levelHeights[0], 0,
                levelHeights[1], 1,
                levelHeights[1], 1,
                levelHeights[1], 1);
}

TEST_C(ReplaceParentsTest, replacesParentsOnDifferentLevels) {
    auto levelHeights = makeLevelHeights({ 1, 2, 5, 6, 10, 11 });

    createRootLevel(levelHeights[0]);
    createLevelWithParents(levelHeights[1],
            levelHeights[0], 0,
            levelHeights[0], 0,
            levelHeights[0], 0);
    createLevelWithParents(levelHeights[2],
            levelHeights[1], 0,
            levelHeights[0], 0,
            levelHeights[1], 1,
            levelHeights[1], 0,
            levelHeights[1], 2);
    createLevelWithParents(levelHeights[3],
            levelHeights[1], 2,
            levelHeights[2], 1,
            levelHeights[2], 4,
            levelHeights[1], 0,
            levelHeights[2], 2);
    createLevelWithParents(levelHeights[4],
            levelHeights[3], 0,
            levelHeights[3], 3,
            levelHeights[2], 4,
            levelHeights[1], 2,
            levelHeights[1], 0,
            levelHeights[2], 0);
    createLevelWithParents(levelHeights[5],
            levelHeights[4], 0,
            levelHeights[2], 1,
            levelHeights[4], 3,
            levelHeights[2], 1,
            levelHeights[4], 2,
            levelHeights[3], 3);

    auto oldParent = getNode(levelHeights[2], 1u);
    auto newParent = getNode(levelHeights[1], 2u);

    levels.replaceParents(oldParent, newParent);

    verifyTree(levelHeights[0],
            levelHeights[1],
                levelHeights[0], 0,
                levelHeights[0], 0,
                levelHeights[0], 0,
            levelHeights[2],
                levelHeights[1], 0,
                levelHeights[0], 0,
                levelHeights[1], 1,
                levelHeights[1], 0,
                levelHeights[1], 2,
            levelHeights[3],
                levelHeights[1], 2,
                levelHeights[1], 2,
                levelHeights[2], 4,
                levelHeights[1], 0,
                levelHeights[2], 2,
            levelHeights[4],
                levelHeights[3], 0,
                levelHeights[3], 3,
                levelHeights[2], 4,
                levelHeights[1], 2,
                levelHeights[1], 0,
                levelHeights[2], 0,
            levelHeights[5],
                levelHeights[4], 0,
                levelHeights[1], 2,
                levelHeights[4], 3,
                levelHeights[1], 2,
                levelHeights[4], 2,
                levelHeights[3], 3);
}
