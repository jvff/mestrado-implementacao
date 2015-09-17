#ifndef COORDINATE_HPP
#define COORDINATE_HPP

struct Coordinate {
    unsigned int x;
    unsigned int y;

    Coordinate() {
    }

    Coordinate(unsigned int x, unsigned int y) : x(x), y(y) {
    }

    Coordinate operator+(const Coordinate& displacement) const {
        return Coordinate(x + displacement.x, y + displacement.y);
    }
};

#endif
