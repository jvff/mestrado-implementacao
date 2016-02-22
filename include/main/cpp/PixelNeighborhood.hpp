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

        return isNeighborAvailable(maskImage, x - 1, y, x > 0)
            || isNeighborAvailable(maskImage, x, y - 1, y > 0)
            || isNeighborAvailable(maskImage, x + 1, y, x < maxX)
            || isNeighborAvailable(maskImage, x, y + 1, y < maxY);
    }

private:
    bool isNeighborAvailable(const Image<bool>& maskImage, unsigned int x,
            unsigned int y, bool neighborCoordinateIsValid) {
        if (neighborCoordinateIsValid == false)
            return false;

        auto neighborHasBeenProcessed = maskImage.getPixelValue(x, y);

        return neighborHasBeenProcessed == false;
    }
};

#endif
