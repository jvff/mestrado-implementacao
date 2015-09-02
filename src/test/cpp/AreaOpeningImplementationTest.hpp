#ifndef AREA_OPENING_IMPLEMENTATION_TEST_HPP
#define AREA_OPENING_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "RectanglePainter.hpp"

class AreaOpeningImplementationTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AreaOpeningImplementationTestData
        : public AbstractFilterImplementationTestData<
                AreaOpeningImplementation<ImageType, ImageType>, ImageType,
                ImageType> {
private:
    using ImplementationType = AreaOpeningImplementation<ImageType, ImageType>;
    using PainterType = RectanglePainter<ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterImplementationTestData<ImplementationType,
            ImageType, ImageType>;
    using ThisType = AreaOpeningImplementationTestData<PixelType, ImageType>;

    std::unique_ptr<PainterType> sourcePainter;
    std::unique_ptr<PainterType> expectedPainter;

    unsigned int maximumPeakSize;

public:
    ~AreaOpeningImplementationTestData() {
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

protected:
    using SuperClass::cancelTestExecution;
    using SuperClass::stateIs;
    using SuperClass::tryToRunTest;

    void finishSetUp() override {
        cancelTestExecution();
    }

    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        return ImplementationType(maximumPeakSize, sourceImage,
                destinationImage);
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningImplementationTestData<PixelType, ImageType>;

#endif
