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

    void raiseNodes() {
        for (auto& leafNode : nodes)
            raiseNode(leafNode);
    }

    void raiseNode(const NodeType& node) {
        nodesToUpdate[node] = node.getLevel() + featureHeight;
    }

    void updateFinalImage() {
        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                updatePixel(x, y);
        }
    }

    void updatePixel(unsigned int x, unsigned int y) {
        auto& node = sourceImage.getPixelNode(x, y);

        destinationImage.setPixel(x, y, nodesToUpdate[node]);
        destinationImage.assignPixelToLatestNode(x, y);
    }
};

#endif
