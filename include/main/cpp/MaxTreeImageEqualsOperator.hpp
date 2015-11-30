#ifndef MAX_TREE_IMAGE_EQUALS_OPERATOR_HPP
#define MAX_TREE_IMAGE_EQUALS_OPERATOR_HPP

template <typename PixelType>
static bool parentNodesAreEqual(const MaxTreeNode<PixelType>& firstNode,
        const MaxTreeNode<PixelType>& secondNode) {
    auto firstParent = firstNode.parent;
    auto secondParent = secondNode.parent;
    bool firstParentExists = (bool)firstParent;
    bool secondParentExists = (bool)secondParent;

    while (firstParentExists && secondParentExists) {
        bool levelsDiffer = firstParent->level != secondParent->level;
        bool idsDiffer = firstParent->id != secondParent->id;

        if (levelsDiffer || idsDiffer)
            return false;

        firstParent = firstParent->parent;
        secondParent = secondParent->parent;
        firstParentExists = (bool)firstParent;
        secondParentExists = (bool)secondParent;
    }

    return !firstParentExists && !secondParentExists;
}

template <typename InternalImageType>
static bool allNodesAreEqual(const MaxTreeImage<InternalImageType>& first,
        const MaxTreeImage<InternalImageType>& second) {
    auto width = first.getWidth();
    auto height = first.getHeight();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto firstNode = first.getNodeOfPixel(x, y);
            auto secondNode = second.getNodeOfPixel(x, y);
            bool nodeParentsDiffer = !parentNodesAreEqual(firstNode,
                    secondNode);

            if (firstNode.id != secondNode.id || nodeParentsDiffer)
                return false;
        }
    }

    return true;
}

template <typename InternalImageType>
bool operator==(const MaxTreeImage<InternalImageType>& first,
        const MaxTreeImage<InternalImageType>& second) {
    return first.getWidth() == second.getWidth()
        && first.getHeight() == second.getHeight()
        && allPixelsAreEqual(first, second)
        && allNodesAreEqual(first, second);
}

#endif
