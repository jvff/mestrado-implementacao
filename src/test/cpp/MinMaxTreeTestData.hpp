#ifndef MIN_MAX_TREE_TEST_DATA_HPP
#define MIN_MAX_TREE_TEST_DATA_HPP

#include <initializer_list>
#include <vector>

#include "MinMaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "ChainableMethodMacros.hpp"
#include "PaintableTestData.hpp"

template <typename PaintableTestDataSuperClass,
        template <typename> class TreeTypeComparator, typename PixelType,
        typename ImageType = SimpleArrayImage<PixelType> >
class MinMaxTreeTestData
        : public PaintableTestData<PaintableTestDataSuperClass, ImageType,
                MinMaxTreeImage<ImageType, TreeTypeComparator<PixelType> > > {
private:
    using ImplementationType = MinMaxTreeImplementation<ImageType, ImageType,
            TreeTypeComparator>;
    using DestinationImageType = MinMaxTreeImage<ImageType,
            TreeTypeComparator<PixelType> >;
    using State = AbstractTestData::State;
    using SuperClass = PaintableTestData<PaintableTestDataSuperClass, ImageType,
            DestinationImageType>;
    using ThisType = MinMaxTreeTestData<PaintableTestDataSuperClass,
            TreeTypeComparator, PixelType, ImageType>;

private:
    std::vector<PixelType> colors;

    using SuperClass::state;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::expectedImage;

public:
    ~MinMaxTreeTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            state = State::READY;
    }

    CHAIN_I(setColorsToUse, PixelType, colorsToUse) {
        for (auto color : colorsToUse)
            colors.push_back(color);
    }

    CHAIN(setBackground, unsigned int colorIndex) {
        auto color = colors[colorIndex];

        SuperClass::setBackground(color);
        SuperClass::setExpectedBackground(color);

        expectedImage->assignPixelToNewNode(0, 0);

        updateExpectedNodes(0, 0, width, height);
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            unsigned int colorIndex) {
        auto color = colors[colorIndex];

        if (stateIs(State::READY)) {
            SuperClass::drawSquare(x, y, size, color);
            SuperClass::drawExpectedSquare(x, y, size, color);

            expectedImage->assignPixelToNewNode(x, y);

            updateExpectedNodes(x, y, x + size, y + size);
        }
    }

    CHAIN(drawSquareOnSameNode, unsigned int x, unsigned int y,
            unsigned int size, unsigned int colorIndex) {
        auto color = colors[colorIndex];

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
