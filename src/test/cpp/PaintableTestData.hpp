#ifndef PAINTABLE_TEST_DATA_HPP
#define PAINTABLE_TEST_DATA_HPP

#include <memory>

#include "AbstractTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "RectanglePainter.hpp"

template <typename SuperClass, typename SourceImageType,
        typename DestinationImageType>
class PaintableTestData : public SuperClass {
private:
    using SourcePainterType = RectanglePainter<SourceImageType>;
    using DestinationPainterType = RectanglePainter<DestinationImageType>;
    using SourcePixelType = typename SourceImageType::PixelType;
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using State = AbstractTestData::State;
    using ThisType = PaintableTestData<SuperClass, SourceImageType,
            DestinationImageType>;

    std::unique_ptr<SourcePainterType> sourcePainter;
    std::unique_ptr<DestinationPainterType> expectedPainter;

public:
    bool setDimensions(unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            sourcePainter.reset(new SourcePainterType(*this->sourceImage));
            expectedPainter.reset(
                    new DestinationPainterType(*this->expectedImage));

            return true;
        } else
            return false;
    }

    CHAIN(setBackground, const SourcePixelType& color) {
        if (stateIs(State::READY))
            sourcePainter->fill(color);
    }

    CHAIN(setExpectedBackground, const DestinationPixelType& color) {
        if (stateIs(State::READY))
            expectedPainter->fill(color);
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const SourcePixelType& color) {
        if (stateIs(State::READY))
            sourcePainter->drawSquare(x, y, size, color);
    }

    CHAIN(drawExpectedSquare, unsigned int x, unsigned int y, unsigned int size,
            const DestinationPixelType& color) {
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

#endif
