#ifndef WATERSHED_FILTER_TEST_HPP
#define WATERSHED_FILTER_TEST_HPP

#include <initializer_list>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "WatershedFilter.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
class WatershedFilterTestData : public AbstractFilterTestData<
        WatershedFilter<SourcePixelType, DestinationPixelType,
                DestinationImageType, SourceImageType>,
        SourcePixelType, DestinationPixelType, DestinationImageType,
        SourceImageType> {
private:
    using State = AbstractTestData::State;
    using FilterType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using SuperClass = AbstractFilterTestData<FilterType, SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;
    using ThisType = WatershedFilterTestData<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    unsigned int gridRows = -1;
    unsigned int gridColumns = -1;
    unsigned int separatorWidth;
    SourcePixelType separatorDepth;
    std::vector<SourcePixelType> gridDepths;
    std::vector<DestinationPixelType> gridOrder;

public:
    ~WatershedFilterTestData() {
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

    void finishSetUp() override {
        *this->sourceImage = [this] (unsigned int x, unsigned int y)
                -> SourcePixelType {
            auto coordinateInfo = getGridIndexForCoordinate(x, y);
            auto index = coordinateInfo.first;
            auto isInSeparator = coordinateInfo.second;

            return isInSeparator ? separatorDepth : gridDepths[index];
        };

        *this->expectedImage = [this] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            auto index = getGridIndexForCoordinate(x, y).first;

            return gridOrder[index];
        };

        this->state = State::READY;
    }

    std::pair<unsigned int, bool> getGridIndexForCoordinate(unsigned int x,
            unsigned int y) {
        auto column = getGridIndexForCoordinate(x, gridColumns, this->width);
        auto row = getGridIndexForCoordinate(y, gridRows, this->height);
        bool isInSeparator = column >= gridColumns || row >= gridRows;

        if (isInSeparator) {
            if (column >= gridColumns)
                column -= gridColumns;

            if (row >= gridRows)
                row -= gridRows;
        }

        unsigned int gridIndex = row * gridColumns + column;

        return std::make_pair(gridIndex, isInSeparator);
    }

    unsigned int getGridIndexForCoordinate(unsigned int coordinate,
            unsigned int numSegments, unsigned int length) {
        unsigned int numSeparators = numSegments - 1;
        unsigned int totalSeparatorSpace = separatorWidth * numSeparators;
        unsigned int lengthWithoutSeparators = length - totalSeparatorSpace;
        unsigned int segmentLength = lengthWithoutSeparators / numSegments;
        unsigned int segmentAndSeparatorLength = segmentLength + separatorWidth;
        unsigned int positionInSegment = coordinate % segmentAndSeparatorLength;
        unsigned int containingSegment = coordinate / segmentAndSeparatorLength;
        unsigned int positionInSeparator = positionInSegment - segmentLength;
        unsigned int separatorMiddle = (separatorWidth - 1) / 2;
        bool coordinateIsInSeparator = positionInSegment >= segmentLength;

        if (coordinateIsInSeparator) {
            if (positionInSeparator <= separatorMiddle)
                return numSegments + containingSegment;
            else
                return numSegments + containingSegment + 1;
        } else
            return containingSegment;
    }
};

#endif
