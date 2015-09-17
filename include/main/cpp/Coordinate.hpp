#ifndef COORDINATE_HPP
#define COORDINATE_HPP

struct Coordinate {
    unsigned int x;
    unsigned int y;

    constexpr Coordinate() : x(0), y(0) {
    }

    Coordinate(unsigned int x, unsigned int y) : x(x), y(y) {
    }

    Coordinate operator+(const Coordinate& displacement) const {
        return Coordinate(x + displacement.x, y + displacement.y);
    }
};

#endif
