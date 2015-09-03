#ifndef COORDINATE_HPP
#define COORDINATE_HPP

struct Coordinate {
    unsigned int x;
    unsigned int y;

    Coordinate() {
    }

    Coordinate(unsigned int x, unsigned int y) : x(x), y(y) {
    }
};

#endif
