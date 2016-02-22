#ifndef PIXEL_NEIGHBORHOOD_HPP
#define PIXEL_NEIGHBORHOOD_HPP

#include "Image.hpp"

template <typename PixelType>
class PixelNeighborhood {
public:
    bool hasAvailableNeighbor(const Image<bool>& maskImage, unsigned int x,
            unsigned int y) {
        auto maxX = maskImage.getWidth() - 1;
        auto maxY = maskImage.getHeight() - 1;

        if (x > 0 && maskImage.getPixelValue(x - 1, y) == false)
            return true;

        if (y > 0 && maskImage.getPixelValue(x, y - 1) == false)
            return true;

        if (x < maxX && maskImage.getPixelValue(x + 1, y) == false)
            return true;

        if (y < maxY && maskImage.getPixelValue(x, y + 1) == false)
            return true;

        return false;
    }
};

#endif
