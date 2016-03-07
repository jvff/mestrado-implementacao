#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_HPP

#include <set>

#include "FilterImplementation.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeNode.hpp"

template <typename InternalImageType, typename LevelOrderComparator>
class MinMaxTreeImageFilterImplementation : public FilterImplementation<
        MinMaxTreeImage<InternalImageType, LevelOrderComparator>,
        MinMaxTreeImage<InternalImageType, LevelOrderComparator> > {
private:
    using PixelType = typename InternalImageType::PixelType;
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using ImageType = MinMaxTreeImage<InternalImageType, LevelOrderComparator>;
    using SuperClass = FilterImplementation<ImageType, ImageType>;

    using SuperClass::sourceImage;

public:
    using SuperClass::SuperClass;

protected:
    std::set<NodeType> collectPixelNodes() {
        std::set<NodeType> pixelNodes;

        pixelNodes.insert(sourceImage.getPixelNode(0, 0));

        return pixelNodes;
    }
};

#endif
