#ifndef HMAX_FILTER_TEST_HPP
#define HMAX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "HmaxFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "RectanglePainter.hpp"

class HmaxFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HmaxFilter<SourceImageType, DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class HmaxFilterTestData : public AbstractFilterTestData<
        HmaxFilter<ImageType, ImageType>, ImageType, ImageType> {
private:
    using FilterType = HmaxFilter<ImageType, ImageType>;
    using PainterType = RectanglePainter<ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterTestData<FilterType, ImageType, ImageType>;
    using ThisType = HmaxFilterTestData<PixelType, ImageType>;

    std::unique_ptr<PainterType> sourcePainter;
    std::unique_ptr<PainterType> expectedPainter;

public:
    virtual ~HmaxFilterTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            sourcePainter.reset(new PainterType(*this->sourceImage));
            expectedPainter.reset(new PainterType(*this->expectedImage));

            this->state = State::SETTING_UP;
        }
    }

    CHAIN(setFeatureHeight, const PixelType& featureHeight) {
        if (stateIs(State::SETTING_UP)) {
            this->initializeFilter(featureHeight);

            this->state = State::READY;
        }
    }

    CHAIN(setBackground, const PixelType& color) {
        if (stateIs(State::READY))
            sourcePainter->fill(color);
    }

    CHAIN(setExpectedBackground, const PixelType& color) {
        if (stateIs(State::READY))
            expectedPainter->fill(color);
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        if (stateIs(State::READY))
            sourcePainter->drawSquare(x, y, size, color);
    }

    CHAIN(drawExpectedSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        if (stateIs(State::READY))
            expectedPainter->drawSquare(x, y, size, color);
    }

protected:
    using SuperClass::cancelTestExecution;
    using SuperClass::stateIs;

    void finishSetUp() override {
        cancelTestExecution();
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = HmaxFilterTestData<PixelType, ImageType>;

#endif
