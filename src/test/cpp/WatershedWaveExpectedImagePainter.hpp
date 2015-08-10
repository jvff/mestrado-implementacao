#ifndef WATERSHED_WAVE_EXPECTED_IMAGE_PAINTER_HPP
#define WATERSHED_WAVE_EXPECTED_IMAGE_PAINTER_HPP

#include <memory>

#include "CoordinateInGridCell.hpp"
#include "Grid.hpp"

class WatershedWaveExpectedImagePainter {
private:
    using Direction = CoordinateInGridCell::Direction;

    static const unsigned char separatorValue = 0;

    const unsigned int size;
    const unsigned int halfPeriods;
    const unsigned int halfPeriodSize;
    const unsigned int periods;

    unsigned int x;
    unsigned int y;

    Grid grid;
    std::unique_ptr<CoordinateInGridCell> coordinate;

public:
    WatershedWaveExpectedImagePainter(unsigned int imageSize,
            unsigned int numberOfHalfPeriods) : size(imageSize),
            halfPeriods(numberOfHalfPeriods),
            halfPeriodSize(size / halfPeriods), periods(halfPeriods / 2),
            grid(size, halfPeriods) {
    }

    unsigned char getPixel(unsigned int x, unsigned int y) {
        this->x = x;
        this->y = y;

        return getPixelValue();
    }

private:
    unsigned char getPixelValue() {
        if (isOnMainDiagonal())
            return separatorValue;

        handleCoordinateOverflow();
        calculateCoordinateInGridCell();

        if (isPeak())
            return drawPeak();
        else
            return drawValley();
    }

    void calculateCoordinateInGridCell() {
        coordinate.reset(new CoordinateInGridCell(x, y, grid));
    }

    bool isPeak() {
        auto row = coordinate->getGridRow();
        auto column = coordinate->getGridColumn();

        return ((row + column) % 2) == 0;
    }

    unsigned char drawValley() {
        if (isSpecialSeparatorInsideValley())
            return separatorValue;
        else
            return calculateGridIndex();
    }

    unsigned char drawPeak() {
        if (isSeparatorInsidePeak())
            return separatorValue;

        updateGridCoordinatesToNearestValley();

        return calculateGridIndex();
    }

    unsigned char calculateGridIndex() {
        return (unsigned char)(coordinate->getGridCellIndex() / 2 + 1);
    }

    bool isSpecialSeparatorInsideValley() {
        return isntOnFirstColumnOrRow() && isFirstPixelOfCell();
    }

    bool isntOnFirstColumnOrRow() {
        bool isOnFirstRow = coordinate->cellIsOnGridExtremity(Direction::UP);
        bool isOnFirstColumn = coordinate->cellIsOnGridExtremity(
                Direction::LEFT);

        return !isOnFirstColumn && !isOnFirstRow;
    }

    bool isFirstPixelOfCell() {
        auto x = coordinate->getX();
        auto y = coordinate->getY();

        return x == 0 && y == 0;
    }

    bool isSeparatorInsidePeak() {
        if (!coordinate->cellIsOnGridExtremity())
            return isOnDiagonal();
        else if (coordinate->cellIsOnGridDiagonal())
            return isOnTopLeftToBottomRightDiagonal();
        else
            return isSeparatorInsideExtremityPeak();
    }

    bool isSeparatorInsideExtremityPeak() {
        return isSeparatorInsideExtremityPeak(Direction::LEFT)
            || isSeparatorInsideExtremityPeak(Direction::RIGHT)
            || isSeparatorInsideExtremityPeak(Direction::UP)
            || isSeparatorInsideExtremityPeak(Direction::DOWN);
    }

    bool isSeparatorInsideExtremityPeak(const Direction& direction) {
        if (coordinate->cellIsOnGridExtremity(direction)) {
            if (coordinate->isCloserToCellEdge(direction))
                return coordinate->isInTheMiddleOfCell(direction);
            else
                return isOnDiagonal();
        } else
            return false;
    }

    void updateGridCoordinatesToNearestValley() {
        Direction direction = coordinate->getNearestSeparator();
        auto row = coordinate->getGridRow();
        auto column = coordinate->getGridColumn();

        switch (direction) {
            case Direction::LEFT:
                column -= 1;
                break;
            case Direction::UP:
                row -= 1;
                break;
            case Direction::RIGHT:
                column += 1;
                break;
            case Direction::DOWN:
                row += 1;
                break;
        };

        coordinate->setGridRow(row);
        coordinate->setGridColumn(column);
    }

    bool isOnMainDiagonal() {
        return x == y;
    }

    bool isOnDiagonal() {
        return isOnBottomLeftToTopRightDiagonal() ||
            isOnTopLeftToBottomRightDiagonal();
    }

    bool isOnBottomLeftToTopRightDiagonal() {
        return coordinate->isOnShiftedBottomLeftToTopRightCellDiagonal(-1);
    }

    bool isOnTopLeftToBottomRightDiagonal() {
        return coordinate->isOnTopLeftToBottomRightCellDiagonal();
    }

    void handleCoordinateOverflow() {
        handleSingleCoordinateOverflow(x, y);
        handleSingleCoordinateOverflow(y, x);
    }

    void handleSingleCoordinateOverflow(unsigned int& u,
            unsigned int& v) {
        if (u == size) {
            if (v == (size - 1))
                --v;

            --u;
        }
    }
};

#endif
