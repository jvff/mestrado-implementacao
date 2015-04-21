#ifndef DUMMY_IMAGE_HPP
#define DUMMY_IMAGE_HPP

#include <cstddef>

#include "Image.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

class DummyImage : public Image<DummyType>, public DestructorInterceptor {
public:
    DummyImage(int width, int height) : Image(width, height) {
    }

    virtual void setPixel(int x, int y, DummyType value) {
    }

    virtual DummyType getPixel(int x, int y) {
        static DummyType dummyValue = { 0 };

        return dummyValue;
    }
};

#endif
