#ifndef INT_ARRAY_IMAGE_H
#define INT_ARRAY_IMAGE_H

#include "Image.h"

class IntArrayImage : public Image {
public:
    IntArrayImage(int width, int height) : Image(width, height) {
    }
};

#endif
