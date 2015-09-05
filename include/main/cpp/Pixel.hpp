#ifndef PIXEL_HPP
#define PIXEL_HPP

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
};

#endif
