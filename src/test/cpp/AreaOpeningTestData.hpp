#ifndef AREA_OPENING_TEST_DATA_HPP
#define AREA_OPENING_TEST_DATA_HPP

#include <memory>

#include "SimpleArrayImage.hpp"

#include "AbstractTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "RectanglePainter.hpp"

template <typename SuperClass, typename PixelType,
        typename ImageType = SimpleArrayImage<PixelType> >
class AreaOpeningTestData : public SuperClass {
private:
    using PainterType = RectanglePainter<ImageType>;
    using State = AbstractTestData::State;
    using ThisType = AreaOpeningTestData<SuperClass, PixelType, ImageType>;

    std::unique_ptr<PainterType> sourcePainter;
    std::unique_ptr<PainterType> expectedPainter;

    unsigned int maximumPeakSize;

public:
    ~AreaOpeningTestData() {
        tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            sourcePainter.reset(new PainterType(*this->sourceImage));
            expectedPainter.reset(new PainterType(*this->expectedImage));

            this->state = State::SETTING_UP;
        }
    }

    CHAIN(setMaximumPeakSize, unsigned int size) {
        if (stateIs(State::SETTING_UP)) {
            maximumPeakSize = size;

            this->state = State::READY;
        }
    }

    CHAIN(setBackground, const PixelType& color) {
        if (stateIs(State::READY)) {
            sourcePainter->fill(color);
            expectedPainter->fill(color);
        }
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        if (stateIs(State::READY)) {
            auto area = size * size;

            sourcePainter->drawSquare(x, y, size, color);

            if (area >= maximumPeakSize)
                expectedPainter->drawSquare(x, y, size, color);
        }
    }

    CHAIN(drawPyramid, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& startHeight) {
        auto height = startHeight;

        if (stateIs(State::READY)) {
            while (size >= 2) {
                drawSquare(x, y, size, height);

                x += 1;
                y += 1;
                size -= 2;
                ++height;
            }
        }
    }

protected:
    using SuperClass::cancelTestExecution;
    using SuperClass::stateIs;
    using SuperClass::tryToRunTest;

    void finishSetUp() override {
        cancelTestExecution();
    }

    unsigned int getMaximumPeakSize() const override {
        return maximumPeakSize;
    }
};

#endif
