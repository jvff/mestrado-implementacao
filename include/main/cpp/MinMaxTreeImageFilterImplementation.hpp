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
    using SuperClass::width;
    using SuperClass::height;

public:
    using SuperClass::SuperClass;

protected:
    std::set<NodeType> collectPixelNodes() {
        std::set<NodeType> pixelNodes;

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                pixelNodes.insert(sourceImage.getPixelNode(x, y));
        }

        return pixelNodes;
    }
};

#endif
