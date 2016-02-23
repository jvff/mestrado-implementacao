#ifndef AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP
#define AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP

#include <map>

#include "FilterImplementation.hpp"
#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeNode.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningMaxTreeImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using PixelType = typename DestinationImageType::PixelType;
    using NodeType = MaxTreeNode<PixelType>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    MaxTreeFilter<SourceImageType, DestinationImageType> maxTreeFilter;
    MaxTreeImage<DestinationImageType> maxTreeImage;

    std::map<NodeType, unsigned int> nodeAreaSizes;

    unsigned int maximumPeakSize;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;

public:
    AreaOpeningMaxTreeImplementation(unsigned int maximumPeakSize,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            maxTreeImage(width, height), maximumPeakSize(maximumPeakSize) {
    }

    void apply() override {
        buildMaxTree();
        filterNodes();
        updateDestinationImage();
    }

private:
    void buildMaxTree() {
        maxTreeImage = maxTreeFilter.apply(sourceImage);
    }

    void filterNodes() {
        auto imageArea = width * height;

        if (maximumPeakSize >= imageArea)
            flattenImage();
        else
            filterNodesWithSmallAreas();
    }

    void flattenImage() {
        auto rootLevel = getRootLevel();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                maxTreeImage.setPixel(x, y, rootLevel);
        }
    }

    PixelType getRootLevel() {
        auto& node = maxTreeImage.getPixelNode(0, 0);

        return walkToRootLevel(node);
    }

    PixelType walkToRootLevel(const NodeType& node) {
        if (isRootNode(node))
            return node.getLevel();
        else
            return walkToRootLevel(node.getParent());
    }

    bool isRootNode(const NodeType& node) {
        return !node.hasParent();
    }

    void filterNodesWithSmallAreas() {
        countAreas();
        propagateAreasFromLeavesToParents();
        removeNodesWithSmallAreas();
    }

    void countAreas() {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                addPixelToAreaCount(x, y);
        }
    }

    void addPixelToAreaCount(unsigned int x, unsigned int y) {
        auto& pixelNode = maxTreeImage.getPixelNode(x, y);
        auto& nodeAreaCounter = getOrCreateNodeAreaCounter(pixelNode);

        ++nodeAreaCounter;
    }

    unsigned int& getOrCreateNodeAreaCounter(const NodeType& node) {
        if (counterForNodeExists(node))
            return getNodeAreaCounter(node);
        else
            return createNodeAreaCounter(node);
    }

    unsigned int& getNodeAreaCounter(const NodeType& node) {
        return nodeAreaSizes[node];
    }

    unsigned int& createNodeAreaCounter(const NodeType& node) {
        auto& counter = nodeAreaSizes[node];

        counter = 0;

        return counter;
    }

    bool counterForNodeExists(const NodeType& node) {
        auto notFound = nodeAreaSizes.end();
        auto searchResult = nodeAreaSizes.find(node);

        return searchResult != notFound;
    }

    void propagateAreasFromLeavesToParents() {
        auto start = nodeAreaSizes.rbegin();
        auto end = nodeAreaSizes.rend();

        for (auto position = start; position != end; ++position) {
            auto& node = position->first;
            auto& area = position->second;

            propagateAreaFromNodeToParent(node, area);
        }
    }

    void propagateAreaFromNodeToParent(const NodeType& node,
            unsigned int area) {
        if (node.hasParent()) {
            auto& parent = node.getParent();

            nodeAreaSizes[parent] += area;
        }
    }

    void removeNodesWithSmallAreas() {
        for (auto&& nodeAreaPair : nodeAreaSizes) {
            auto& node = nodeAreaPair.first;
            auto& area = nodeAreaPair.second;

            if (area < maximumPeakSize)
                maxTreeImage.removeNode(node);
        }
    }

    void updateDestinationImage() {
        destinationImage.paint(maxTreeImage);
    }
};

#endif
