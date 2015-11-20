#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <cmath>

struct Coordinate {
    unsigned int x;
    unsigned int y;

    constexpr Coordinate() : x(0), y(0) {
    }

    constexpr Coordinate(unsigned int x, unsigned int y) : x(x), y(y) {
    }

    float distanceTo(Coordinate other) const {
        float deltaX = (float)x - (float)other.x;
        float deltaY = (float)y - (float)other.y;

        float squaredDeltaX = deltaX * deltaX;
        float squaredDeltaY = deltaY * deltaY;

        return std::sqrt(squaredDeltaX + squaredDeltaY);
    }

    Coordinate operator+(const Coordinate& displacement) const {
        return Coordinate(x + displacement.x, y + displacement.y);
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }

    bool operator<(const Coordinate& other) const {
        return x < other.x && y < other.y;
    }

    bool isBefore(const Coordinate& other) const {
        if (x != other.x)
            return x < other.x;
        else
            return y < other.y;
    }

    bool isAfter(const Coordinate& other) const {
        if (x != other.x)
            return x > other.x;
        else
            return y > other.y;
    }

    struct AscendingComparator {
        bool operator() (const Coordinate& first, const Coordinate& second)
                const {
            return first.isBefore(second);
        }
    };
};

#endif
