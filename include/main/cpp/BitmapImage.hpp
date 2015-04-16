#ifndef BITMAP_IMAGE_HPP
#define BITMAP_IMAGE_HPP

#include "Image.hpp"

class BitmapImage : public Image<bool> {
public:
    BitmapImage(int width, int height) : Image(width, height) {
    }
};

#endif
