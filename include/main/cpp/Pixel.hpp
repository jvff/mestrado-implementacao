#ifndef PIXEL_HPP
#define PIXEL_HPP

#include "Coordinate.hpp"

template <typename Type>
struct Pixel {
    unsigned int x;
    unsigned int y;
    Type value;

    Pixel() {
    }

    Pixel(unsigned int x, unsigned int y, const Type& value) : x(x), y(y),
            value(value) {
    }

    Pixel(const Coordinate& coordinate, const Type& value) : x(coordinate.x),
            y(coordinate.y), value(value) {
    }

    bool isBefore(const Pixel<Type>& other) const {
        if (value != other.value)
            return value < other.value;
        else if (x != other.x)
            return x < other.x;
        else
            return y < other.y;
    }

    bool isAfter(const Pixel<Type>& other) const {
        if (value != other.value)
            return value > other.value;
        else if (x != other.x)
            return x > other.x;
        else
            return y > other.y;
    }

    struct AscendingComparator {
        bool operator() (const Pixel<Type>& first, const Pixel<Type>& second)
                const {
            return first.isBefore(second);
        }
    };
};

#endif
