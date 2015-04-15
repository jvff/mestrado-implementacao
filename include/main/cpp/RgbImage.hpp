#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include "Image.hpp"

class RgbImage : public Image<int> {
public:
    RgbImage(int width, int height) : Image(width, height) {
    }
};

#endif
