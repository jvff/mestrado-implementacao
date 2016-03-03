#ifndef HMIN_MIN_TREE_IMPLEMENTATION_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_HPP

#include <map>
#include <set>

#include "FilterImplementation.hpp"
#include "MinTreeImage.hpp"
#include "MinTreeNode.hpp"

template <typename InternalImageType>
class HminMinTreeImplementation : public FilterImplementation<
        MinTreeImage<InternalImageType>, MinTreeImage<InternalImageType> > {
private:
    using ImageType = MinTreeImage<InternalImageType>;
    using PixelType = typename InternalImageType::PixelType;
    using NodeType = MinTreeNode<PixelType>;
    using SuperClass = FilterImplementation<ImageType, ImageType>;

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
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                nodes.insert(sourceImage.getPixelNode(x, y));
        }
    }

    void findLeafNodes() {
        leafNodes = nodes;

        for (auto& node : nodes)
            removeNodeParentChainFromLeafNodeSet(node);
    }

    void removeNodeParentChainFromLeafNodeSet(const NodeType& node) {
        if (node.hasParent())
            removeNodeChainFromLeafNodeSet(node.getParent());
    }

    void removeNodeChainFromLeafNodeSet(const NodeType& node) {
        if (leafNodeSetHas(node)) {
            leafNodes.erase(node);

            removeNodeParentChainFromLeafNodeSet(node);
        }
    }

    bool leafNodeSetHas(const NodeType& node) {
        auto notFound = leafNodes.end();
        auto searchResult = leafNodes.find(node);

        return searchResult != notFound;
    }

    void raiseNodes() {
        for (auto& leafNode : leafNodes)
            raiseNode(leafNode);
    }

    void raiseNode(const NodeType& node) {
        auto newHeight = node.getLevel() + featureHeight;

        raiseNodeTo(node, newHeight);
    }

    void raiseNodeTo(const NodeType& node, const PixelType& newLevelHeight) {
        nodesToUpdate[node] = newLevelHeight;

        maybeRaiseNodeParentTo(node, newLevelHeight);
    }

    void maybeRaiseNodeParentTo(const NodeType& node,
            const PixelType& newLevelHeight) {
        if (node.hasParent()) {
            auto& parent = node.getParent();

            if (parent.getLevel() < newLevelHeight)
                raiseNodeTo(parent, newLevelHeight);
        }
    }

    void updateFinalImage() {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                updatePixel(x, y);
        }
    }

    void updatePixel(unsigned int x, unsigned int y) {
        auto& node = sourceImage.getPixelNode(x, y);

        if (nodeShouldBeUpdated(node))
            destinationImage.setPixel(x, y, nodesToUpdate[node]);
        else
            destinationImage.setPixel(x, y, sourceImage.getPixelValue(x, y));

        destinationImage.assignPixelToLatestNode(x, y);
    }

    bool nodeShouldBeUpdated(const NodeType& node) {
        auto notFound = nodesToUpdate.end();
        auto searchResult = nodesToUpdate.find(node);

        return searchResult != notFound;
    }
};

#endif
