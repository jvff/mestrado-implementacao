#ifndef HMIN_MIN_TREE_IMPLEMENTATION_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_HPP

#include <functional>
#include <map>
#include <set>

#include <boost/range/adaptor/reversed.hpp>

#include "MinMaxTreeImageFilterImplementation.hpp"
#include "MinTreeImage.hpp"
#include "MinTreeNode.hpp"

template <typename InternalImageType>
class HminMinTreeImplementation : public MinMaxTreeImageFilterImplementation<
        InternalImageType,
        std::greater<typename InternalImageType::PixelType> > {
private:
    using ImageType = MinTreeImage<InternalImageType>;
    using PixelType = typename InternalImageType::PixelType;
    using NodeType = MinTreeNode<PixelType>;
    using LevelOrderComparator = std::greater<PixelType>;
    using SuperClass = MinMaxTreeImageFilterImplementation<InternalImageType,
            LevelOrderComparator>;

    PixelType featureHeight;

    std::set<NodeType> nodes;
    std::set<NodeType> leafNodes;
    std::map<NodeType, PixelType> nodesToUpdate;

    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

public:
    HminMinTreeImplementation(const PixelType& featureHeight,
            const ImageType& sourceImage, ImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            featureHeight(featureHeight) {
    }

    void apply() override {
        collectNodes();
        findLeafNodes();
        raiseNodes();
        updateFinalImage();
    }

private:
    void collectNodes() {
        nodes = SuperClass::collectPixelNodes();
    }

    void findLeafNodes() {
        leafNodes = SuperClass::getLeafNodesIn(nodes);
    }

    void raiseNodes() {
        for (auto& leafNode : boost::adaptors::reverse(leafNodes))
            raiseNode(leafNode);
    }

    void raiseNode(const NodeType& node) {
        auto newHeight = node.getLevel() + featureHeight;

        raiseNodeTo(node, newHeight);
    }

    void raiseNodeTo(const NodeType& node, PixelType newHeight) {
        if (node.hasParent())
            newHeight = getRaisedHeightAfterUpdatingParent(node, newHeight);

        nodesToUpdate[node] = newHeight;
    }

    PixelType getRaisedHeightAfterUpdatingParent(const NodeType& node,
            const PixelType& newLevelHeight) {
        auto& parent = node.getParent();
        auto parentIsntQueuedYet = nodeIsMarkedForUpdate(parent) == false;
        auto touchesParentLevel = parent.getLevel() <= newLevelHeight;

        if (touchesParentLevel) {
            if (parentIsntQueuedYet)
                raiseNodeTo(parent, newLevelHeight);

            return nodesToUpdate[parent];
        } else
            return newLevelHeight;
    }

    void updateFinalImage() {
        updateFinalImagePixels();
        updateFinalImageNodes();
    }

    void updateFinalImagePixels() {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                updatePixel(x, y);
        }
    }

    void updatePixel(unsigned int x, unsigned int y) {
        auto& node = sourceImage.getPixelNode(x, y);

        if (nodeIsMarkedForUpdate(node))
            destinationImage.setPixel(x, y, nodesToUpdate[node]);
        else
            destinationImage.setPixel(x, y, sourceImage.getPixelValue(x, y));
    }

    bool nodeIsMarkedForUpdate(const NodeType& node) {
        auto notFound = nodesToUpdate.end();
        auto searchResult = nodesToUpdate.find(node);

        return searchResult != notFound;
    }

    void updateFinalImageNodes() {
        for (auto& node : nodes)
            updatePixelsAssociatedToNode(node);
    }

    void updatePixelsAssociatedToNode(const NodeType& node) {
        auto nodeLevel = getUpdatedNodeLevel(node);
        auto nodeId = node.getId();
        auto nodeExists = nodeWasCollapsedIntoParent(node, nodeLevel);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                updatePixelIfAssociatedToNode(x, y, nodeLevel, nodeId,
                        nodeExists);
            }
        }
    }

    PixelType getUpdatedNodeLevel(const NodeType& node) {
        if (nodeIsMarkedForUpdate(node))
            return nodesToUpdate[node];
        else
            return node.getLevel();
    }

    bool nodeWasCollapsedIntoParent(const NodeType& node,
            const PixelType& updatedLevel) {
        if (nodeIsMarkedForUpdate(node) && node.hasParent()) {
            auto& parent = node.getParent();
            auto parentLevel = parent.getLevel();

            if (nodeIsMarkedForUpdate(parent))
                parentLevel = nodesToUpdate[parent];

            return updatedLevel == parentLevel;
        } else
            return false;
    }

    void updatePixelIfAssociatedToNode(unsigned int x, unsigned int y,
            PixelType nodeLevel, unsigned int nodeId, bool& nodeExists) {
        auto pixelLevel = destinationImage.getPixelValue(x, y);

        if (pixelLevel == nodeLevel) {
            auto& oldNode = sourceImage.getPixelNode(x, y);

            if (oldNode.getId() == nodeId)
                assignPixelToNode(x, y, nodeExists);
        }
    }

    void assignPixelToNode(unsigned int x, unsigned int y, bool& nodeExists) {
        if (nodeExists)
            destinationImage.assignPixelToLatestNode(x, y);
        else {
            destinationImage.assignPixelToNewNode(x, y);

            nodeExists = true;
        }
    }
};

#endif
