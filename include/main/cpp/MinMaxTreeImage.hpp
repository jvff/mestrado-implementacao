#ifndef MIN_MAX_TREE_IMAGE_HPP
#define MIN_MAX_TREE_IMAGE_HPP

#include "Image.hpp"
#include "MinMaxTree.hpp"
#include "MinMaxTreeNode.hpp"
#include "SimpleArrayImage.hpp"

template <typename InternalImageType, typename LevelOrderComparator>
class MinMaxTreeImage : public Image<typename InternalImageType::PixelType> {
public:
    using PixelType = typename InternalImageType::PixelType;

private:
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using SuperClass = Image<PixelType>;

    InternalImageType internalImage;
    SimpleArrayImage<unsigned int> nodeIdImage;

    MinMaxTree<PixelType, LevelOrderComparator> minMaxTree;

    LevelOrderComparator levelOrderComparator;

    using SuperClass::width;
    using SuperClass::height;

public:
    MinMaxTreeImage(unsigned int width, unsigned int height)
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

        if (minMaxTree.hasLevel(level))
            assignPixelToNode(x, y, minMaxTree.getLatestNodeOnLevel(level));
        else
            assignPixelToNode(x, y, minMaxTree.addNode(level));
    }

    void assignPixelToNewNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);

        assignPixelToNode(x, y, minMaxTree.addNode(level));
    }

    void connectPixels(unsigned int firstX, unsigned int firstY,
            unsigned int secondX, unsigned int secondY) {
        auto& firstNode = getPixelNode(firstX, firstY);
        auto& secondNode = getPixelNode(secondX, secondY);

        if (firstNode.hasParent())
            connectPixelsMaybeReplacingParent(firstNode, secondNode);
        else
            connectPixelsWithoutParents(firstNode, secondNode);
    }

    const NodeType& getPixelNode(unsigned int x, unsigned int y) const {
        auto level = internalImage.getPixelValue(x, y);
        auto id = nodeIdImage.getPixelValue(x, y);

        return minMaxTree.getNode(level, id);
    }

    void removeNode(const NodeType& node) {
        auto level = node.getLevel();

        if (minMaxTree.hasLevel(level))
            safelyRemoveNode(node);
    }

    bool operator==(const MinMaxTreeImage& other) const {
        return internalImage == other.internalImage
            &&  nodeIdImage == other.nodeIdImage
            &&  minMaxTree == other.minMaxTree;
    }

    using SuperClass::getPixelValue;
    using SuperClass::setPixel;

private:
    void assignPixelToNode(unsigned int x, unsigned int y,
            const NodeType& node) {
        nodeIdImage.setPixel(x, y, node.getId());
    }

    void connectPixelsMaybeReplacingParent(const NodeType& firstNode,
            const NodeType& secondNode) {
        auto& isBefore = levelOrderComparator;
        auto firstNodeParentLevel = firstNode.getParent().getLevel();
        auto secondNodeLevel = secondNode.getLevel();

        if (isBefore(firstNodeParentLevel, secondNodeLevel))
            minMaxTree.setNodeParent(firstNode, secondNode);
    }

    void connectPixelsWithoutParents(const NodeType& firstNode,
            const NodeType& secondNode) {
        minMaxTree.setNodeParent(firstNode, secondNode);
    }

    void safelyRemoveNode(const NodeType& node) {
        auto& realNode = getRealNodeInTree(node);

        if (realNode.hasParent())
            removeNormalNode(realNode);
        else
            removeRootNode(node);
    }

    const NodeType& getRealNodeInTree(const NodeType& reference) {
        auto level = reference.getLevel();
        auto id = reference.getId();

        return minMaxTree.getNode(level, id);
    }

    void removeNormalNode(const NodeType& node) {
        auto& parent = node.getParent();
        auto newColor = parent.getLevel();
        auto newId = parent.getId();

        updatePixelsIfAssignedToNode(node, newColor, newId);

        minMaxTree.removeNode(node.getLevel(), node.getId());
    }

    void removeRootNode(const NodeType& node) {
        minMaxTree.removeNode(node.getLevel(), node.getId());

        auto newColor = minMaxTree.getFirstLevel();
        auto newId = 0u;

        updatePixelsIfOnCollapsedLevel(newColor, newId);
        updatePixelsIfAssignedToNode(node, newColor, newId);
    }

    void updatePixelsIfAssignedToNode(const NodeType& node, PixelType newColor,
            unsigned int newId) {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                updatePixelIfAssignedToNode(x, y, node, newColor, newId);
        }
    }

    void updatePixelIfAssignedToNode(unsigned int x, unsigned int y,
            const NodeType& node, PixelType newColor, unsigned int newId) {
        if (pixelIsAssignedToNode(x, y, node)) {
            internalImage.setPixel(x, y, newColor);
            nodeIdImage.setPixel(x, y, newId);
        }
    }

    bool pixelIsAssignedToNode(unsigned int x, unsigned int y,
            const NodeType& node) {
        auto pixelNodeId = nodeIdImage.getPixelValue(x, y);
        auto pixelNodeLevel = internalImage.getPixelValue(x, y);

        return pixelNodeId == node.getId() && pixelNodeLevel == node.getLevel();
    }

    void updatePixelsIfOnCollapsedLevel(PixelType newColor,
            unsigned int newId) {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                updatePixelIfOnCollapsedLevel(x, y, newColor, newId);
        }
    }

    void updatePixelIfOnCollapsedLevel(unsigned int x, unsigned int y,
            PixelType newColor, unsigned int newId) {
        if (pixelIsOnLevel(x, y, newColor))
            nodeIdImage.setPixel(x, y, newId);
    }

    bool pixelIsOnLevel(unsigned int x, unsigned int y, PixelType level) {
        auto pixelLevel = internalImage.getPixelValue(x, y);

        return pixelLevel == level;
    }
};

#endif
