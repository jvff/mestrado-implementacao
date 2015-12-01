#ifndef MAX_TREE_TEST_DATA_HPP
#define MAX_TREE_TEST_DATA_HPP

#include "MaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "ChainableMethodMacros.hpp"
#include "PaintableTestData.hpp"

template <typename PaintableTestDataSuperClass, typename PixelType,
        typename ImageType = SimpleArrayImage<PixelType> >
class MaxTreeTestData : public PaintableTestData<PaintableTestDataSuperClass,
        ImageType, MaxTreeImage<ImageType> > {
private:
    using ImplementationType = MaxTreeImplementation<ImageType, ImageType>;
    using DestinationImageType = MaxTreeImage<ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = PaintableTestData<PaintableTestDataSuperClass, ImageType,
            DestinationImageType>;
    using ThisType = MaxTreeTestData<PaintableTestDataSuperClass, PixelType,
            ImageType>;

    using SuperClass::state;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::expectedImage;

public:
    ~MaxTreeTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            state = State::READY;
    }

    CHAIN(setBackground, const PixelType& color) {
        SuperClass::setBackground(color);
        SuperClass::setExpectedBackground(color);

        expectedImage->assignPixelToNewNode(0, 0);

        updateExpectedNodes(0, 0, width, height);
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        if (stateIs(State::READY)) {
            SuperClass::drawSquare(x, y, size, color);
            SuperClass::drawExpectedSquare(x, y, size, color);

            expectedImage->assignPixelToNewNode(x, y);

            updateExpectedNodes(x, y, x + size, y + size);
        }
    }

    CHAIN(drawSquareOnSameNode, unsigned int x, unsigned int y,
            unsigned int size, const PixelType& color) {
        if (stateIs(State::READY)) {
            SuperClass::drawSquare(x, y, size, color);
            SuperClass::drawExpectedSquare(x, y, size, color);

            updateExpectedNodes(x, y, x + size, y + size);
        }
    }

private:
    using SuperClass::stateIs;

    void updateExpectedNodes(unsigned int startX, unsigned int startY,
            unsigned int endX, unsigned int endY) {
        for (auto x = startX; x < endX; ++x) {
            for (auto y = startY; y < endY; ++y)
                expectedImage->assignPixelToLatestNode(x, y);
        }
    }
};

#endif
