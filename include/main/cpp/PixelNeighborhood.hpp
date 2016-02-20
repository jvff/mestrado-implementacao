#ifndef PIXEL_NEIGHBORHOOD_HPP
#define PIXEL_NEIGHBORHOOD_HPP

#include "Image.hpp"

template <typename PixelType>
class PixelNeighborhood {
public:
    bool hasAvailableNeighbor(const Image<bool>&, unsigned int, unsigned int) {
        return true;
    }
};

#endif
