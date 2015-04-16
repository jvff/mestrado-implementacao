#ifndef GRAYSCALE_IMAGE_HPP
#define GRAYSCALE_IMAGE_HPP

#include "Image.hpp"

class GrayscaleImage : public Image<int> {
public:
    GrayscaleImage(int width, int height) : Image(width, height) {
    }
};

#endif
