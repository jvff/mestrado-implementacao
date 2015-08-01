#ifndef WATERSHED_FILTER_TEST_HPP
#define WATERSHED_FILTER_TEST_HPP

#include <initializer_list>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"
#include "WatershedFilter.hpp"

#include "AbstractTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
class WatershedFilterTestData : public AbstractTestData {
private:
    using FilterType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using DestinationImagePointer = std::unique_ptr<DestinationImageType>;
    using SourceImagePointer = std::unique_ptr<SourceImageType>;
    using ThisType = WatershedFilterTestData<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    unsigned int width;
    unsigned int height;

    unsigned int gridRows = -1;
    unsigned int gridColumns = -1;
    unsigned int separatorWidth;
    SourcePixelType separatorDepth;
    std::vector<SourcePixelType> gridDepths;
    std::vector<DestinationPixelType> gridOrder;

public:
    FilterType filter;
    SourceImagePointer sourceImage;
    DestinationImagePointer expectedImage;

public:
    ~WatershedFilterTestData() {
        tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int newWidth, unsigned int newHeight) {
        if (stateIs(State::EMPTY)) {
            width = newWidth;
            height = newHeight;

            sourceImage.reset(new SourceImageType(width, height));
            expectedImage.reset(new DestinationImageType(width, height));

            state = State::READY;
        }
    }

    CHAIN(useSegmentGrid, unsigned int rows, unsigned int columns) {
        if (!gridDepths.empty() || !gridOrder.empty())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            state = State::SETTING_UP;

            gridRows = rows;
            gridColumns = columns;

            gridDepths.resize(rows * columns);
            gridOrder.resize(rows * columns);
        }
    }

    CHAIN(setSeparatorWidth, unsigned int newSeparatorWidth) {
        if (stateIs({State::READY, State::SETTING_UP})) {
            state = State::SETTING_UP;

            separatorWidth = newSeparatorWidth;
        }
    }

    CHAIN(setSeparatorDepth, SourcePixelType newSeparatorDepth) {
        if (stateIs({State::READY, State::SETTING_UP})) {
            state = State::SETTING_UP;

            separatorDepth = newSeparatorDepth;
        }
    }

    CHAIN_I(setSegmentDepths, SourcePixelType, depths) {
        if (depths.size() != gridDepths.capacity())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            state = State::SETTING_UP;

            gridDepths = depths;
        }
    }

    CHAIN_I(setSegmentOrder, DestinationPixelType, labels) {
        if (labels.size() != gridOrder.capacity())
            cancelTestExecution();
        else if (stateIs({State::READY, State::SETTING_UP})) {
            state = State::SETTING_UP;

            gridOrder = labels;
        }
    }

private:
    void finishSetUp() override {
        *sourceImage = [this] (unsigned int x, unsigned int y) -> SourcePixelType {
            auto coordinateInfo = getGridIndexForCoordinate(x, y);
            auto index = coordinateInfo.first;
            auto isInSeparator = coordinateInfo.second;

            return isInSeparator ? separatorDepth : gridDepths[index];
        };

        *expectedImage = [this] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            auto index = getGridIndexForCoordinate(x, y).first;

            return gridOrder[index];
        };

        state = State::READY;
    }

    std::pair<unsigned int, bool> getGridIndexForCoordinate(unsigned int x,
            unsigned int y) {
        unsigned int column = getGridIndexForCoordinate(x, gridColumns, width);
        unsigned int row = getGridIndexForCoordinate(y, gridRows, height);
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

    void runTest() override {
        auto result = filter.apply(*sourceImage);

        assertThat(result).isEqualTo(*expectedImage);
    }
};

#endif
