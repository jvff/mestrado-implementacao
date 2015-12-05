#ifndef MAX_TREE_IMAGE_TEST_HPP
#define MAX_TREE_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

class MaxTreeImageTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;
    using TreeNodeType = MaxTreeNode<PixelType>;
    using TreeNodePointer = std::shared_ptr<TreeNodeType>;
    using MaxTreeNodeFunction =
            std::function<TreeNodeType(unsigned int, unsigned int)>;

protected:
    void paintImage(Image<PixelType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                image.setPixel(x, y, PixelType{ (int)(x + y * width) });
        }
    }

    void verifyPaintedImagePixels(const Image<PixelType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                auto pixelValue = image.getPixelValue(x, y);
                auto expectedValue = PixelType{ (int)(x + y * width) };

                assertThat(pixelValue).isEqualTo(expectedValue);
            }
        }
    }

    void fillImage(Image<PixelType>& image, PixelType color) {
        image = [color] (unsigned int, unsigned int) -> PixelType {
            return color;
        };
    }

    void assignPixelsToLatestNodes(MaxTreeImage<InternalImageType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto y = 0u; y < height; ++y) {
            for (auto x = 0u; x < width; ++x)
                image.assignPixelToLatestNode(x, y);
        }
    }

    TreeNodePointer makeNode(unsigned int id, PixelType level) {
        return std::make_shared<TreeNodeType>(level, id);
    }

    TreeNodePointer makeNode(unsigned int id, PixelType level,
            TreeNodePointer parent) {
        return std::make_shared<TreeNodeType>(parent, level, id);
    }

    void verifyNodes(const MaxTreeImage<InternalImageType>& image,
            const TreeNodePointer& expectedRootNodePointer) {
        verifyNodes(image, *expectedRootNodePointer);
    }

    void verifyNodes(const MaxTreeImage<InternalImageType>& image,
            const TreeNodeType& expectedRootNode) {
        auto expectedNodeFunction = [expectedRootNode] (unsigned int,
                unsigned int) -> TreeNodeType {
            return expectedRootNode;
        };

        verifyNodes(image, expectedNodeFunction);
    }

    void verifyNodes(const MaxTreeImage<InternalImageType>& image,
            MaxTreeNodeFunction expectedNodeFunction) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                auto expectedNode = expectedNodeFunction(x, y);

                verifyNode(image.getNodeOfPixel(x, y), expectedNode);
            }
        }
    }

    void verifyNode(const TreeNodeType& node,
            const TreeNodePointer& expectedNodePointer) {
        verifyNode(node, *expectedNodePointer);
    }

    void verifyNode(const TreeNodeType& node,
            const TreeNodeType& expectedNode) {
        verifyNodeData(node, expectedNode);
        verifyNodeParents(node, expectedNode);
    }

    void verifyNodeData(const TreeNodeType& node,
            const TreeNodeType& expectedNode) {
        assertThat(node.id).isEqualTo(expectedNode.id);
        assertThat(node.level).isEqualTo(expectedNode.level);
    }

    void verifyNodeParents(const TreeNodeType& node,
            const TreeNodeType& expectedNode) {
        auto parent = node.parent;
        auto expectedParent = expectedNode.parent;
        auto parentExists = (bool)parent;
        auto expectedParentExists = (bool)expectedParent;

        while (parentExists && expectedParentExists) {
            verifyNodeData(*parent, *expectedParent);

            parent = parent->parent;
            expectedParent = expectedParent->parent;
            parentExists = (bool)parent;
            expectedParentExists = (bool)expectedParent;
        }

        assertThat(parentExists).isEqualTo(expectedParentExists);
    }
};

#endif
