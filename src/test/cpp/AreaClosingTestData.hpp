#ifndef AREA_CLOSING_TEST_DATA_HPP
#define AREA_CLOSING_TEST_DATA_HPP

#include <memory>

#include "AreaClosingFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "RectanglePainter.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AreaClosingTestData : public AbstractFilterTestData<
        AreaClosingFilter<ImageType, ImageType>, ImageType, ImageType> {
private:
    using FilterType = AreaClosingFilter<ImageType, ImageType>;
    using PainterType = RectanglePainter<ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterTestData<FilterType, ImageType, ImageType>;
    using ThisType = AreaClosingTestData<PixelType, ImageType>;

    std::unique_ptr<PainterType> sourcePainter;
    std::unique_ptr<PainterType> expectedPainter;

    unsigned int maximumHoleSize;

public:
    ~AreaClosingTestData() {
        tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            sourcePainter.reset(new PainterType(*this->sourceImage));
            expectedPainter.reset(new PainterType(*this->expectedImage));

            this->state = State::SETTING_UP;
        }
    }

    CHAIN(setMaximumHoleSize, unsigned int size) {
        if (stateIs(State::SETTING_UP)) {
            maximumHoleSize = size;

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

            if (area >= maximumHoleSize)
                expectedPainter->drawSquare(x, y, size, color);
        }
    }

private:
    using SuperClass::cancelTestExecution;
    using SuperClass::stateIs;
    using SuperClass::tryToRunTest;

    void finishSetUp() override {
        cancelTestExecution();
    }

    void runTest() override {
        this->initializeFilter(maximumHoleSize);

        SuperClass::runTest();
    }
};

#endif
