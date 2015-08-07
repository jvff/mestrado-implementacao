#ifndef WATERSHED_TEST_DATA_HPP
#define WATERSHED_TEST_DATA_HPP

#include <initializer_list>
#include <vector>

#include "SimpleArrayImage.hpp"

#include "AbstractTestData.hpp"
#include "ChainableMethodMacros.hpp"

template <typename SuperClass, typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
class WatershedTestData : public SuperClass {
private:
    using State = AbstractTestData::State;
    using ThisType = WatershedTestData<SuperClass, SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    unsigned int gridRows = -1;
    unsigned int gridColumns = -1;
    unsigned int separatorWidth;
    SourcePixelType separatorDepth;
    std::vector<SourcePixelType> gridDepths;
    std::vector<DestinationPixelType> gridOrder;

public:
    ~WatershedTestData() {
        tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int newWidth, unsigned int newHeight) {
        SuperClass::setDimensions(newWidth, newHeight);
    }

    CHAIN(useSegmentGrid, unsigned int rows, unsigned int columns) {
        if (!gridDepths.empty() || !gridOrder.empty())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            this->state = State::SETTING_UP;

            gridRows = rows;
            gridColumns = columns;

            gridDepths.resize(rows * columns);
            gridOrder.resize(rows * columns);
        }
    }

    CHAIN(setSeparatorWidth, unsigned int newSeparatorWidth) {
        if (stateIs({State::READY, State::SETTING_UP})) {
            this->state = State::SETTING_UP;

            separatorWidth = newSeparatorWidth;
        }
    }

    CHAIN(setSeparatorDepth, SourcePixelType newSeparatorDepth) {
        if (stateIs({State::READY, State::SETTING_UP})) {
            this->state = State::SETTING_UP;

            separatorDepth = newSeparatorDepth;
        }
    }

    CHAIN_I(setSegmentDepths, SourcePixelType, depths) {
        if (depths.size() != gridDepths.capacity())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            this->state = State::SETTING_UP;

            gridDepths = depths;
        }
    }

    CHAIN_I(setSegmentOrder, DestinationPixelType, labels) {
        if (labels.size() != gridOrder.capacity())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            this->state = State::SETTING_UP;

            gridOrder = labels;
        }
    }

private:
    using SuperClass::cancelTestExecution;
    using SuperClass::stateIs;
    using SuperClass::tryToRunTest;

    struct CoordinateInfo {
        unsigned int gridIndex;
        bool isInSeparator;
        bool isInTheMiddleOfTheSeparator;
    };

    void finishSetUp() override {
        *this->sourceImage = [this] (unsigned int x, unsigned int y)
                -> SourcePixelType {
            auto coordinate = locateCoordinate(x, y);

            if (coordinate.isInSeparator)
                return separatorDepth;
            else
                return gridDepths[coordinate.gridIndex];
        };

        *this->expectedImage = [this] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            auto coordinate = locateCoordinate(x, y);

            if (coordinate.isInTheMiddleOfTheSeparator)
                return 0;
            else
                return gridOrder[coordinate.gridIndex];
        };

        this->state = State::READY;
    }

    CoordinateInfo locateCoordinate(unsigned int x, unsigned int y) {
        CoordinateInfo coordinate = { 0, false, false };

        auto column = locateCoordinate(x, gridColumns, this->width, coordinate);
        auto row = locateCoordinate(y, gridRows, this->height, coordinate);

        coordinate.gridIndex = row * gridColumns + column;

        return coordinate;
    }

    unsigned int locateCoordinate(unsigned int position,
            unsigned int numSegments, unsigned int length,
            CoordinateInfo& coordinate) {
        unsigned int numSeparators = numSegments - 1;
        unsigned int totalSeparatorSpace = separatorWidth * numSeparators;
        unsigned int lengthWithoutSeparators = length - totalSeparatorSpace;
        unsigned int segmentLength = lengthWithoutSeparators / numSegments;
        unsigned int segmentAndSeparatorLength = segmentLength + separatorWidth;
        unsigned int positionInSegment = position % segmentAndSeparatorLength;
        unsigned int containingSegment = position / segmentAndSeparatorLength;
        unsigned int positionInSeparator = positionInSegment - segmentLength;
        bool isInSeparator = positionInSegment >= segmentLength;

        if (isInSeparator) {
            return locateCoordinateThatIsInSeparator(positionInSeparator,
                    containingSegment, coordinate);
        } else
            return containingSegment;
    }

    unsigned int locateCoordinateThatIsInSeparator(
            unsigned int positionInSeparator,
            unsigned int segmentBeforeSeparator,
            CoordinateInfo& coordinate) {
        unsigned int separatorMiddle = (separatorWidth - 1) / 2;
        unsigned int segmentAfterSeparator = segmentBeforeSeparator + 1;

        coordinate.isInSeparator = true;
        coordinate.isInTheMiddleOfTheSeparator |=
                isInTheMiddle(positionInSeparator, separatorWidth);

        if (positionInSeparator > separatorMiddle)
            return segmentAfterSeparator;
        else
            return segmentBeforeSeparator;
    }

    bool isInTheMiddle(unsigned int position, unsigned int size) {
        bool hasMiddle = (size % 2) == 1;

        if (!hasMiddle)
            return false;

        unsigned int middle = size / 2;

        return position == middle;
    }
};

#endif
