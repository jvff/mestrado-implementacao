#ifndef BITMAP_IMAGE_HPP
#define BITMAP_IMAGE_HPP

#include "Image.hpp"

class BitmapImage : public Image<bool> {
public:
    BitmapImage(unsigned int width, unsigned int height)
            : Image(width, height) {
    }
};

#endif
