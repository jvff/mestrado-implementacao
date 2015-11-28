#ifndef MAX_TREE_IMAGE_HPP
#define MAX_TREE_IMAGE_HPP

#include "Image.hpp"
#include "MaxTreeNode.hpp"

template <typename InternalImageType>
class MaxTreeImage : public Image<typename InternalImageType::PixelType> {
private:
    using PixelType = typename InternalImageType::PixelType;
    using NodeType = MaxTreeNode<PixelType>;
    using SuperClass = Image<PixelType>;

    InternalImageType internalImage;

public:
    MaxTreeImage(unsigned int width, unsigned int height)
            : SuperClass(width, height), internalImage(width, height) {
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    void assignPixelToLatestNode(unsigned int, unsigned int) {
    }

    NodeType getNodeOfPixel(unsigned int x, unsigned int y) {
        NodeType node;

        node.level = getPixelValue(x, y);
        node.id = 0;

        return node;
    }
};

#endif
