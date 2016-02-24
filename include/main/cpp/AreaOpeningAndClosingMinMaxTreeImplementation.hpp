#ifndef AREA_OPENING_AND_CLOSING_MIN_MAX_TREE_IMPLEMENTATION_HPP
#define AREA_OPENING_AND_CLOSING_MIN_MAX_TREE_IMPLEMENTATION_HPP

#include <map>

#include "FilterImplementation.hpp"
#include "MinMaxTreeFilter.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeNode.hpp"

template <typename SourceImageType, typename DestinationImageType,
        template <typename> class TreeTypeComparator>
class AreaOpeningAndClosingMinMaxTreeImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using PixelType = typename DestinationImageType::PixelType;
    using LevelOrderComparator = TreeTypeComparator<PixelType>;
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using MinMaxTreeFilterType = MinMaxTreeFilter<SourceImageType,
            DestinationImageType, TreeTypeComparator>;
    using MinMaxTreeImageType = MinMaxTreeImage<DestinationImageType,
            LevelOrderComparator>;

    MinMaxTreeFilterType minMaxTreeFilter;
    MinMaxTreeImageType minMaxTreeImage;

    std::map<NodeType, unsigned int> nodeAreaSizes;

    unsigned int areaThreshold;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;

public:
    AreaOpeningAndClosingMinMaxTreeImplementation(unsigned int areaThreshold,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            minMaxTreeImage(width, height), areaThreshold(areaThreshold) {
    }

    void apply() override {
        buildMinMaxTree();
        filterNodes();
        updateDestinationImage();
    }

private:
    void buildMinMaxTree() {
        minMaxTreeImage = minMaxTreeFilter.apply(sourceImage);
    }

    void filterNodes() {
        auto imageArea = width * height;

        if (areaThreshold >= imageArea)
            flattenImage();
        else
            filterNodesWithSmallAreas();
    }

    void flattenImage() {
        auto rootLevel = getRootLevel();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                minMaxTreeImage.setPixel(x, y, rootLevel);
        }
    }

    PixelType getRootLevel() {
        auto& node = minMaxTreeImage.getPixelNode(0, 0);

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
        auto& pixelNode = minMaxTreeImage.getPixelNode(x, y);
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

            if (area < areaThreshold)
                minMaxTreeImage.removeNode(node);
        }
    }

    void updateDestinationImage() {
        destinationImage.paint(minMaxTreeImage);
    }
};

#endif
