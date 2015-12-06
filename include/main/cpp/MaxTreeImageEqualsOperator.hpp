#ifndef MAX_TREE_IMAGE_EQUALS_OPERATOR_HPP
#define MAX_TREE_IMAGE_EQUALS_OPERATOR_HPP

template <typename PixelType>
static bool parentNodesAreEqual(const MaxTreeNode<PixelType>& firstNode,
        const MaxTreeNode<PixelType>& secondNode) {
    if (firstNode.hasParent() != secondNode.hasParent())
        return false;

    if (firstNode.hasParent()) {
        auto& firstParent = firstNode.getParent();
        auto& secondParent = secondNode.getParent();
        bool levelsDiffer = firstParent.getLevel() != secondParent.getLevel();
        bool idsDiffer = firstParent.getId() != secondParent.getId();

        if (levelsDiffer || idsDiffer)
            return false;
        else
            return parentNodesAreEqual(firstParent, secondParent);
    } else
        return true;
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

            if (firstNode.getId() != secondNode.getId() || nodeParentsDiffer)
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
