#ifndef COORDINATE_IN_GRID_CELL_HPP
#define COORDINATE_IN_GRID_CELL_HPP

#include <algorithm>
#include <initializer_list>

#include "Grid.hpp"

class CoordinateInGridCell {
private:
    unsigned int cellWidth;
    unsigned int cellHeight;

    unsigned int x;
    unsigned int y;

    unsigned int gridRow;
    unsigned int gridColumn;

    unsigned int distanceToLeftEdge;
    unsigned int distanceToTopEdge;
    unsigned int distanceToRightEdge;
    unsigned int distanceToBottomEdge;

    const Grid& grid;

public:
    enum class Direction { LEFT, RIGHT, UP, DOWN };

public:
    CoordinateInGridCell(unsigned int gridX, unsigned int gridY,
            const Grid& parentGrid) : grid(parentGrid) {
        cellWidth = grid.getCellWidth();
        cellHeight = grid.getCellHeight();

        x = gridX % cellWidth;
        y = gridY % cellHeight;

        gridColumn = gridX / cellWidth;
        gridRow = gridY / cellWidth;

        distanceToLeftEdge = x;
        distanceToTopEdge = y;
        distanceToRightEdge = cellWidth - x - 1;
        distanceToBottomEdge = cellHeight - y - 1;
    }

    unsigned int getGridCellIndex() {
        return gridColumn * grid.getNumberOfRows() + gridRow;
    }

    unsigned int getX() {
        return x;
    }

    unsigned int getY() {
        return y;
    }

    unsigned int getGridRow() {
        return gridRow;
    }

    unsigned int getGridColumn() {
        return gridColumn;
    }

    void setGridRow(unsigned int row) {
        gridRow = std::min(row, grid.getNumberOfRows());
    }

    void setGridColumn(unsigned int column) {
        gridColumn = std::min(column, grid.getNumberOfColumns());
    }

    bool cellIsOnGridExtremity() {
        for (auto direction : getAllDirections()) {
            if (cellIsOnGridExtremity(direction))
                return true;
        }

        return false;
    }

    bool cellIsOnGridDiagonal() {
        return gridColumn == gridRow;
    }

    bool cellIsOnGridExtremity(const Direction& direction) {
        unsigned int first = 0;
        unsigned int lastColumn = grid.getNumberOfColumns() - 1;
        unsigned int lastRow = grid.getNumberOfRows() - 1;

        switch (direction) {
            case Direction::LEFT:
                return gridColumn == first;
            case Direction::RIGHT:
                return gridColumn == lastColumn;
            case Direction::UP:
                return gridRow == first;
            case Direction::DOWN:
                return gridRow == lastRow;
        };

        return false;
    }

    bool isCloserToCellEdge(const Direction& direction) {
        switch (direction) {
            case Direction::LEFT:
                return distanceToRightEdge > distanceToLeftEdge;
            case Direction::RIGHT:
                return distanceToRightEdge < distanceToLeftEdge;
            case Direction::UP:
                return distanceToTopEdge < distanceToBottomEdge;
            case Direction::DOWN:
                return distanceToTopEdge > distanceToBottomEdge;
        };

        return false;
    };

    bool isInTheMiddleOfCell(const Direction& direction) {
        switch (direction) {
            case Direction::LEFT:
            case Direction::RIGHT:
                return distanceToTopEdge == (distanceToBottomEdge + 1);
            case Direction::UP:
            case Direction::DOWN:
                return distanceToLeftEdge == (distanceToRightEdge + 1);
        };

        return false;
    }

    Direction getNearestSeparator() {
        auto smallestDistance = std::max(cellWidth, cellHeight);
        Direction nearestSeparator;

        for (auto direction : getAllDirections()) {
            if (!cellIsOnGridExtremity(direction)) {
                auto distance = distanceToEdge(direction);

                if (distance < smallestDistance) {
                    smallestDistance = distance;
                    nearestSeparator = direction;
                }
            }
        }

        return nearestSeparator;
    }

    std::initializer_list<Direction> getAllDirections() {
        return { Direction::LEFT, Direction::UP, Direction::RIGHT,
                Direction::DOWN };
    }

    unsigned int distanceToEdge(const Direction& direction) {
        switch (direction) {
            case Direction::LEFT:
                return distanceToLeftEdge;
            case Direction::RIGHT:
                return distanceToRightEdge;
            case Direction::UP:
                return distanceToTopEdge;
            case Direction::DOWN:
                return distanceToBottomEdge;
        };

        return 0;
    }

    bool isOnShiftedBottomLeftToTopRightCellDiagonal(int amountToShift) {
        unsigned int shiftAmount;

        if (amountToShift < 0) {
            shiftAmount = (unsigned int)(-amountToShift);

            return distanceToTopEdge == (distanceToRightEdge + shiftAmount);
        } else {
            shiftAmount = (unsigned int)amountToShift;

            return (distanceToTopEdge + shiftAmount) == distanceToRightEdge;
        }
    }

    bool isOnTopLeftToBottomRightCellDiagonal() {
        return distanceToTopEdge == distanceToLeftEdge;
    }
};

#endif
