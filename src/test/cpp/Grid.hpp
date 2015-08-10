#ifndef GRID_HPP
#define GRID_HPP

class Grid {
private:
    unsigned int width;
    unsigned int height;

    unsigned int rows;
    unsigned int columns;

    unsigned int cellWidth;
    unsigned int cellHeight;

public:
    Grid(unsigned int width, unsigned int height, unsigned int rows,
            unsigned int columns) : width(width), height(height), rows(rows),
            columns(columns) {
        cellWidth = width / columns;
        cellHeight = height / rows;
    }

    Grid(unsigned int sideLength, unsigned int cellsPerSide)
            : Grid(sideLength, sideLength, cellsPerSide, cellsPerSide) {
    }

    unsigned int getNumberOfRows() const {
        return rows;
    }

    unsigned int getNumberOfColumns() const {
        return columns;
    }

    unsigned int getCellWidth() const {
        return cellWidth;
    }

    unsigned int getCellHeight() const {
        return cellHeight;
    }
};

#endif
