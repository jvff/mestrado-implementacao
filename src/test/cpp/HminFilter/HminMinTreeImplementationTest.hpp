#ifndef HMIN_MIN_TREE_IMPLEMENTATION_TEST_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminMinTreeImplementation.hpp"
#include "MinTreeImage.hpp"
#include "Pixel.hpp"
#include "SimpleArrayImage.hpp"

#include "../AbstractFilterImplementationTestData.hpp"
#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#include "HminTestData.hpp"

class HminMinTreeImplementationTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using ImageType = MinTreeImage<InternalImageType>;
    using DummyImplementation = HminMinTreeImplementation<InternalImageType>;
};

template <typename ParentTestDataType, typename PixelType,
        typename InternalImageType = SimpleArrayImage<PixelType> >
class HminMinTreeTestData
        : public HminTestData<ParentTestDataType, PixelType,
                MinTreeImage<InternalImageType> > {
private:
    using ImageType = MinTreeImage<InternalImageType>;
    using SuperClass = HminTestData<ParentTestDataType, PixelType, ImageType>;
    using ThisType = HminMinTreeTestData<ParentTestDataType, PixelType,
            InternalImageType>;

private:
    Pixel<PixelType> sourceRootLevelPixel;
    Pixel<PixelType> expectedRootLevelPixel;

protected:
    using SuperClass::sourceImage;
    using SuperClass::expectedImage;

public:
    CHAIN(setBackground, const PixelType& color) {
        SuperClass::setBackground(color);

        assignNodeToAllPixels(*sourceImage);

        sourceRootLevelPixel = sourceImage->getPixel(0, 0);
    }

    CHAIN(setExpectedBackground, const PixelType& color) {
        SuperClass::setExpectedBackground(color);

        assignNodeToAllPixels(*expectedImage);

        expectedRootLevelPixel = sourceImage->getPixel(0, 0);
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        SuperClass::drawSquare(x, y, size, color);

        assignNewNodeToPixelsInSquare(x, y, size, *sourceImage);

        maybeUpdateRootLevel(*sourceImage, sourceRootLevelPixel, color, x, y);
    }

    CHAIN(drawExpectedSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        SuperClass::drawExpectedSquare(x, y, size, color);

        assignNewNodeToPixelsInSquare(x, y, size, *expectedImage);

        maybeUpdateRootLevel(*expectedImage, expectedRootLevelPixel, color, x,
                y);
    }

    CHAIN_PARENT_METHOD(setDimensions)
    CHAIN_PARENT_METHOD(setFeatureHeight)

private:
    void assignNodeToAllPixels(ImageType& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                image.assignPixelToLatestNode(x, y);
        }
    }

    void assignNewNodeToPixelsInSquare(unsigned int startX, unsigned int startY,
            unsigned int size, ImageType& image) {
        auto endX = startX + size;
        auto endY = startY + size;

        image.assignPixelToNewNode(startX, startY);

        for (auto x = startX; x < endX; ++x) {
            for (auto y = startY; y < endY; ++y)
                image.assignPixelToLatestNode(x, y);
        }
    }

    void maybeUpdateRootLevel(ImageType& image,
            Pixel<PixelType>& rootLevelPixel, PixelType paintedColor,
            unsigned int x, unsigned int y) {
        if (paintedColor > rootLevelPixel.value) {
            auto oldX = rootLevelPixel.x;
            auto oldY = rootLevelPixel.y;

            image.connectPixels(oldX, oldY, x, y);

            rootLevelPixel = image.getPixel(x, y);
        }
    }
};

template <typename PixelType,
        typename InternalImageType = SimpleArrayImage<PixelType> >
class HminMinTreeImplementationTestData
        : public AbstractFilterImplementationTestData<
                HminMinTreeImplementation<InternalImageType>,
                MinTreeImage<InternalImageType>,
                MinTreeImage<InternalImageType> > {
private:
    using ImageType = MinTreeImage<InternalImageType>;
    using ImplementationType = HminMinTreeImplementation<InternalImageType>;

protected:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        PixelType featureHeight = getFeatureHeight();

        return ImplementationType(featureHeight, sourceImage, destinationImage);
    }

    virtual PixelType getFeatureHeight() = 0;
};

template <typename PixelType,
        typename InternalImageType = SimpleArrayImage<PixelType> >
using TestData = HminMinTreeTestData<
        HminMinTreeImplementationTestData<PixelType, InternalImageType>,
        PixelType, InternalImageType>;

#endif
