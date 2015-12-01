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
    using MaxTreeNodeFunction =
            std::function<MaxTreeNode<PixelType>(unsigned int, unsigned int)>;

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

    std::shared_ptr<MaxTreeNode<PixelType> > makeNode(unsigned int id,
            PixelType level) {
        auto node = std::make_shared<MaxTreeNode<PixelType> >();

        node->id = id;
        node->level = level;

        return node;
    }

    std::shared_ptr<MaxTreeNode<PixelType> > makeNode(unsigned int id,
            PixelType level, std::shared_ptr<MaxTreeNode<PixelType> > parent) {
        auto node = makeNode(id, level);

        node->parent = parent;

        return node;
    }

    void verifyNodes(const MaxTreeImage<InternalImageType>& image,
            const MaxTreeNode<PixelType> expectedRootNode) {
        auto expectedNodeFunction = [expectedRootNode] (unsigned int,
                unsigned int) -> MaxTreeNode<PixelType> {
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

    void verifyNode(const MaxTreeNode<PixelType> node,
            const MaxTreeNode<PixelType> expectedNode) {
        verifyNodeData(node, expectedNode);
        verifyNodeParents(node, expectedNode);
    }

    void verifyNodeData(const MaxTreeNode<PixelType> node,
            const MaxTreeNode<PixelType> expectedNode) {
        assertThat(node.id).isEqualTo(expectedNode.id);
        assertThat(node.level).isEqualTo(expectedNode.level);
    }

    void verifyNodeParents(const MaxTreeNode<PixelType> node,
            const MaxTreeNode<PixelType> expectedNode) {
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
