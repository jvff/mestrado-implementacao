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
