#ifndef ABSTRACT_FIXTURE_HPP
#define ABSTRACT_FIXTURE_HPP

#include <initializer_list>
#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MinMaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"
#include "../NodeVerificationHelper.hpp"

template <typename TypeParameter>
class AbstractFixture : public ::testing::Test,
        public NodeVerificationHelper<DummyType, TypeParameter> {
protected:
    using LevelOrderComparator = TypeParameter;
    using PixelType = DummyType;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using DummyMinMaxTreeImageType = MinMaxTreeImage<InternalImageType,
            LevelOrderComparator>;
    using TreeNodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using TreeNodePointer = std::shared_ptr<TreeNodeType>;
    using MinMaxTreeNodeFunction =
            std::function<TreeNodeType(unsigned int, unsigned int)>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;
    using NodeVerificationHelperType = NodeVerificationHelper<PixelType,
            TypeParameter>;

protected:
    std::vector<DummyType> makeLevelHeights(
            std::initializer_list<int> heightValues) {
        std::vector<DummyType> heightsToSort;

        for (auto height : heightValues)
            heightsToSort.push_back(DummyType{ height });

        return sortLevelHeights(heightsToSort);
    }

    void paintImage(Image<PixelType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();
        auto pixels = getPixelsToPaint(width, height);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                image.setPixel(x, y, pixels(x, y));
        }
    }

    void verifyPaintedImagePixels(const Image<PixelType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();
        auto pixels = getPixelsToPaint(width, height);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                auto pixelValue = image.getPixelValue(x, y);
                auto expectedValue = pixels(x, y);

                assertThat(pixelValue).isEqualTo(expectedValue);
            }
        }
    }

    void fillImage(Image<PixelType>& image, PixelType color) {
        image = [color] (unsigned int, unsigned int) -> PixelType {
            return color;
        };
    }

    void assignPixelsToLatestNodes(DummyMinMaxTreeImageType& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto y = 0u; y < height; ++y) {
            for (auto x = 0u; x < width; ++x)
                image.assignPixelToLatestNode(x, y);
        }
    }

    void verifyNodes(const DummyMinMaxTreeImageType& image,
            const TreeNodePointer& expectedRootNodePointer) {
        verifyNodes(image, *expectedRootNodePointer);
    }

    void verifyNodes(const DummyMinMaxTreeImageType& image,
            const TreeNodeType& expectedRootNode) {
        auto expectedNodeFunction = [expectedRootNode] (unsigned int,
                unsigned int) -> TreeNodeType {
            return expectedRootNode;
        };

        verifyNodes(image, expectedNodeFunction);
    }

    void verifyNodes(const DummyMinMaxTreeImageType& image,
            MinMaxTreeNodeFunction expectedNodeFunction) {
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

    virtual PaintFunction getPixelsToPaint(unsigned int width,
            unsigned int height) = 0;

protected:
    using NodeVerificationHelperType::makeNode;
    using NodeVerificationHelperType::verifyNode;

private:
    std::vector<DummyType> sortLevelHeights(std::vector<DummyType>& heights) {
        LevelOrderComparator comparator;

        std::sort(heights.begin(), heights.end(), comparator);

        return heights;
    }
};

template <typename TypeParameter>
class MinMaxTreeImageTest : public AbstractFixture<TypeParameter> {
protected:
    using SuperClass = AbstractFixture<TypeParameter>;
    using PaintFunction = typename SuperClass::PaintFunction;
    using PixelType = typename SuperClass::PixelType;

protected:
    virtual PaintFunction getPixelsToPaint(unsigned int width, unsigned int)
            override {
        return [=] (unsigned int x, unsigned int y) -> PixelType {
            return PixelType{ (int)(x + y * width) };
        };
    }
};

template <typename PixelType>
class MinMaxTreeImageTest<std::greater<PixelType> >
        : public AbstractFixture<std::greater<PixelType> > {
protected:
    using TypeParameter = std::greater<PixelType>;
    using SuperClass = AbstractFixture<TypeParameter>;
    using PaintFunction = typename SuperClass::PaintFunction;

protected:
    virtual PaintFunction getPixelsToPaint(unsigned int width,
            unsigned int height) override {
        auto size = width * height;

        return [=] (unsigned int x, unsigned int y) -> PixelType {
            return PixelType{ (int)(size - (x + y * width) - 1) };
        };
    }
};

#endif
