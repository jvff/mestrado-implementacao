#ifndef ABSTRACT_FIXTURE_HPP
#define ABSTRACT_FIXTURE_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"
#include "../NodeVerificationHelper.hpp"

template <typename TypeParameter>
class MaxTreeImageTest : public ::testing::Test,
        public NodeVerificationHelper<DummyType, TypeParameter> {
protected:
    using PixelType = DummyType;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;
    using TreeNodeType = MaxTreeNode<PixelType>;
    using TreeNodePointer = std::shared_ptr<TreeNodeType>;
    using MaxTreeNodeFunction =
            std::function<TreeNodeType(unsigned int, unsigned int)>;
    using NodeVerificationHelperType = NodeVerificationHelper<PixelType,
            TypeParameter>;

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

    void verifyFilledImagePixels(Image<PixelType>& image, PixelType color) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                assertThat(image.getPixelValue(x, y)).isEqualTo(color);
        }
    }

protected:
    using NodeVerificationHelperType::makeNode;
    using NodeVerificationHelperType::verifyNode;
};

#endif
