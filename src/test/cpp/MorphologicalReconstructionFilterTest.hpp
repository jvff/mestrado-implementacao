#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class MorphologicalReconstructionFilterTestData {
private:
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using ImagePointer = std::unique_ptr<ImageType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;
    using ThisType = MorphologicalReconstructionFilterTestData<PixelType,
            ImageType>;

    enum class State { EMPTY, SETTING_UP, CANCELLED };

public:
    State state = State::EMPTY;

    FilterType filter;
    ImagePointer sourceImage;
    ImagePointer markerImage;
    ImagePointer expectedImage;

    PixelType background;
    PixelType foreground;
    PixelType markerDepth;

    unsigned int width;
    unsigned int height;
    unsigned int maxX;
    unsigned int maxY;

public:
    ~MorphologicalReconstructionFilterTestData<PixelType, ImageType>() {
        if (state == State::SETTING_UP)
            applyFilterAndVerifyResult();
        else
            failTest();
    }

    CHAIN(setDimensions, unsigned int newWidth, unsigned int newHeight) {
        if (state != State::EMPTY)
            cancelTestExecution();
        else {
            width = newWidth;
            height = newHeight;

            maxX = width - 1;
            maxY = height - 1;

            sourceImage.reset(new ImageType(width, height));
            markerImage.reset(new ImageType(width, height));
            expectedImage.reset(new ImageType(width, height));

            state = State::SETTING_UP;
        }
    }

    CHAIN(setBackground, PixelType value) {
        background = value;

        if (state != State::SETTING_UP)
            cancelTestExecution();
        else {
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

    void addMarker(unsigned int x, unsigned int y) {
        addMarker(x, y, markerDepth);
    }

    void addMarker(unsigned int x, unsigned int y, PixelType depth) {
        markerImage->setPixel(x, y, depth);
    }

private:
    void applyFilterAndVerifyResult() {
        filter.apply(*sourceImage, *markerImage);

        assertThat(*markerImage).isEqualTo(*expectedImage);
    }

    void cancelTestExecution() {
        state = State::CANCELLED;
    }

    void failTest() {
        FAIL() << "Test was incorrectly set-up";
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
