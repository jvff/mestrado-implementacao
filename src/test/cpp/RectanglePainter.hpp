#ifndef RECTANGLE_PAINTER_HPP
#define RECTANGLE_PAINTER_HPP

#include "Image.hpp"

template <typename ImageType>
class RectanglePainter {
private:
    using PixelType = typename ImageType::PixelType;

    struct Rectangle {
        unsigned int startX;
        unsigned int startY;
        unsigned int endX;
        unsigned int endY;

        bool contains(unsigned int x, unsigned int y) {
            return isBetween(startX, x, endX) && isBetween(startY, y, endY);
        }

        bool isBetween(unsigned int start, unsigned int middle,
                unsigned int end) {
            return start <= middle && middle <= end;
        }
    };

protected:
    ImageType& image;

public:
    RectanglePainter(ImageType& targetImage) : image(targetImage) {
    }

    void fill(const PixelType& color) {
        image = [&color] (unsigned int, unsigned int) -> PixelType {
            return color;
        };
    }

    void drawRectangle(unsigned int startX, unsigned startY, unsigned int endX,
            unsigned int endY, const PixelType& color) {
        Rectangle rectangle = { startX, startY, endX, endY };

        image = [&] (unsigned int x, unsigned int y) -> PixelType {
            if (rectangle.contains(x, y))
                return color;
            else
                return image.getPixel(x, y);
        };
    }

    void drawSquare(unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        auto startX = x;
        auto startY = y;
        auto endX = x + size - 1;
        auto endY = y + size - 1;

        drawRectangle(startX, startY, endX, endY, color);
    }
};

#endif
