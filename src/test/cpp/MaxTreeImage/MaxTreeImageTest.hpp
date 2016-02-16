#ifndef MAX_TREE_IMAGE_TEST_HPP
#define MAX_TREE_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "../CustomTypedTestMacros.hpp"
#include "../DummyTypes.hpp"

template <typename TypeParameter>
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

                verifyNode(image.getPixelNode(x, y), expectedNode);
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
        assertThat(node.getId()).isEqualTo(expectedNode.getId());
        assertThat(node.getLevel()).isEqualTo(expectedNode.getLevel());
    }

    void verifyNodeParents(const TreeNodeType& node,
            const TreeNodeType& expectedNode) {
        assertThat(node.hasParent()).isEqualTo(expectedNode.hasParent());

        if (node.hasParent() && expectedNode.hasParent()) {
            auto& parent = node.getParent();
            auto& expectedParent = expectedNode.getParent();

            verifyNodeData(parent, expectedParent);
            verifyNodeParents(parent, expectedParent);
        }
    }
};

using nodeLevelComparatorTypes = ::testing::Types<std::less<DummyType> >;

#define SUB_TEST(testFixture) \
    CREATE_EMPTY_MAX_TREE_IMAGE_TEST_FIXTURE(MaxTreeImage##testFixture); \
    TYPED_TEST_CASE(MaxTreeImage##testFixture, nodeLevelComparatorTypes)

#define CREATE_EMPTY_MAX_TREE_IMAGE_TEST_FIXTURE(testFixture) \
template <typename TypeParameter> \
class testFixture : public MaxTreeImageTest<TypeParameter> { \
}

#define TEST_C(testFixture, testName) \
    CREATE_MAX_TREE_IMAGE_TEST_CLASS(MaxTreeImage##testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeImage##testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeImage##testFixture, testName)

#define CREATE_MAX_TREE_IMAGE_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
\
    using DummyMaxTreeImageType = typename SuperClass::DummyMaxTreeImageType; \
    using PixelType = typename SuperClass::PixelType; \
    using TreeNodePointer = typename SuperClass::TreeNodePointer; \
    using TreeNodeType = typename SuperClass::TreeNodeType; \
\
    using SuperClass::assignPixelsToLatestNodes; \
    using SuperClass::fillImage; \
    using SuperClass::makeNode; \
    using SuperClass::paintImage; \
    using SuperClass::verifyNode; \
    using SuperClass::verifyNodes; \
    using SuperClass::verifyPaintedImagePixels; \
\
    virtual void TestBody(); \
}

#endif
