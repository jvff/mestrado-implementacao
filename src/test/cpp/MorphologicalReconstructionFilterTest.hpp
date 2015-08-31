#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractImageTransformationTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class MorphologicalReconstructionFilterTestData
        : public AbstractImageTransformationTestData<PixelType, PixelType,
                ImageType, ImageType> {
private:
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using ImagePointer = std::unique_ptr<ImageType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;
    using SuperClass = AbstractImageTransformationTestData<PixelType, PixelType,
            ImageType, ImageType>;
    using State = typename SuperClass::State;
    using ThisType = MorphologicalReconstructionFilterTestData<PixelType,
            ImageType>;

public:
    FilterType filter;
    ImagePointer markerImage;

    PixelType background;
    PixelType foreground;
    PixelType markerDepth;

    unsigned int maxX;
    unsigned int maxY;

    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::sourceImage;
    using SuperClass::expectedImage;

public:
    ~MorphologicalReconstructionFilterTestData<PixelType, ImageType>() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int newWidth, unsigned int newHeight) {
        if (SuperClass::setDimensions(newWidth, newHeight)) {
            maxX = width - 1;
            maxY = height - 1;

            markerImage.reset(new ImageType(width, height));

            this->state = State::SETTING_UP;
        }
    }

    CHAIN(setBackground, PixelType value) {
        if (stateIs(State::SETTING_UP)) {
            background = value;

            *markerImage = [this] (unsigned int, unsigned int) -> PixelType {
                return background;
            };
        }
    }

    CHAIN(setForeground, PixelType value) {
        foreground = value;
    }

    CHAIN(setMarkerDepth, PixelType value) {
        markerDepth = value;
    }

    void useLeftToRightHorizontalLine() {
        useHorizontalLine();
        addMarker(1, height / 2);
    }

    void useRightToLeftHorizontalLine() {
        useHorizontalLine();
        addMarker(width - 2, height / 2);
    }

    void useTopToBottomVerticalLine() {
        useVerticalLine();
        addMarker(width / 2, 1);
    }

    void useBottomToTopVerticalLine() {
        useVerticalLine();
        addMarker(width / 2, height - 2);
    }

    void useRectangleWithTopLeftMarker() {
        useRectangle();
        addMarker(1, 1);
    }

    void useRectangleWithBottomRightMarker() {
        useRectangle();
        addMarker(width - 2, height - 2);
    }

    void useRectangleWithCenterMarker() {
        useRectangle();
        addMarker(width / 2, height / 2);
    }

    void useRectangleOnTheTopLeftCornerWithBottomRightMarker() {
        const unsigned int startX = 0;
        const unsigned int startY = 0;
        const unsigned int endX = maxX - 1;
        const unsigned int endY = maxY - 1;

        useRectangle(startX, startY, endX, endY);
        addMarker(endX, endY);
    }

    void useFullImageWithCenterMarker() {
        useRectangle(0, 0, maxX, maxY);
        addMarker(width / 2, height / 2);
    }

    void addMarker(unsigned int x, unsigned int y) {
        addMarker(x, y, markerDepth);
    }

    void addMarker(unsigned int x, unsigned int y, PixelType depth) {
        markerImage->setPixel(x, y, depth);
    }

private:
    using SuperClass::stateIs;

    void finishSetUp() {
        this->state = State::READY;
    }

    ImageType transformImage() override {
        filter.apply(*sourceImage, *markerImage);

        return *markerImage;
    }

    void useHorizontalLine() {
        const unsigned int startX = 1;
        const unsigned int startY = height / 2;
        const unsigned int endX = maxX - 1;
        const unsigned int endY = height / 2;

        useRectangle(startX, startY, endX, endY);
    }

    void useVerticalLine() {
        const unsigned int startX = width / 2;
        const unsigned int startY = 1;
        const unsigned int endX = width / 2;
        const unsigned int endY = maxY - 1;

        useRectangle(startX, startY, endX, endY);
    }

    void useRectangle() {
        const unsigned int startX = 1;
        const unsigned int startY = 1;
        const unsigned int endX = maxX - 1;
        const unsigned int endY = maxY - 1;

        useRectangle(startX, startY, endX, endY);
    }

    void useRectangle(unsigned int startX, unsigned int startY,
            unsigned int endX, unsigned int endY) {
        *sourceImage = fillRectangle(startX, startY, endX, endY, foreground);
        *expectedImage = fillRectangle(startX, startY, endX, endY, markerDepth);
    }

    PaintFunction fillRectangle(unsigned int startX, unsigned int startY,
            unsigned int endX, unsigned int endY, PixelType foreground) {
        return [=] (unsigned int x, unsigned int y) -> PixelType {
            if (x >= startX && y >= startY && x <= endX && y <= endY)
                return foreground;
            else
                return background;
        };
    }
};

#endif
