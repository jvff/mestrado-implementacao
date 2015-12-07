#ifndef MAX_TREE_IMAGE_HPP
#define MAX_TREE_IMAGE_HPP

#include "Image.hpp"
#include "MaxTree.hpp"
#include "MaxTreeNode.hpp"
#include "SimpleArrayImage.hpp"

template <typename InternalImageType>
class MaxTreeImage : public Image<typename InternalImageType::PixelType> {
public:
    using PixelType = typename InternalImageType::PixelType;

private:
    using NodeType = MaxTreeNode<PixelType>;
    using SuperClass = Image<PixelType>;

    InternalImageType internalImage;
    SimpleArrayImage<unsigned int> nodeIdImage;

    MaxTree<PixelType> maxTree;

public:
    MaxTreeImage(unsigned int width, unsigned int height)
            : SuperClass(width, height), internalImage(width, height),
            nodeIdImage(width, height) {
    }

    using SuperClass::operator=;

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    void assignPixelToLatestNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);

        if (maxTree.hasLevel(level))
            assignPixelToNode(x, y, maxTree.getLatestNodeOnLevel(level));
        else
            assignPixelToNode(x, y, maxTree.addNode(level));
    }

    void assignPixelToNewNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);

        assignPixelToNode(x, y, maxTree.addNode(level));
    }

    void connectPixels(unsigned int firstX, unsigned int firstY,
            unsigned int secondX, unsigned int secondY) {
        auto& firstNode = getPixelNode(firstX, firstY);
        auto& secondNode = getPixelNode(secondX, secondY);

        if (secondNode.getLevel() > firstNode.getParent().getLevel())
            maxTree.setNodeParent(firstNode, secondNode);
    }

    const NodeType& getPixelNode(unsigned int x, unsigned int y) const {
        auto level = internalImage.getPixelValue(x, y);
        auto id = nodeIdImage.getPixelValue(x, y);

        return maxTree.getNode(level, id);
    }

    using SuperClass::getPixelValue;
    using SuperClass::setPixel;

private:
    void assignPixelToNode(unsigned int x, unsigned int y,
            const MaxTreeNode<PixelType>& node) {
        nodeIdImage.setPixel(x, y, node.getId());
    }
};

template <typename InternalImageType>
static bool allNodesAreEqual(const MaxTreeImage<InternalImageType>& first,
        const MaxTreeImage<InternalImageType>& second) {
    auto width = first.getWidth();
    auto height = first.getHeight();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto firstNode = first.getPixelNode(x, y);
            auto secondNode = second.getPixelNode(x, y);

            if (!firstNode.isEquivalentTo(secondNode))
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
