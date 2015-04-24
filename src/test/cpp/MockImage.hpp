#ifndef MOCK_IMAGE_HPP
#define MOCK_IMAGE_HPP

#include <cstddef>

#include <gmock/gmock.h>

#include "Image.hpp"

#include "DestructorInterceptor.hpp"

template <typename PixelType>
class MockImage : public Image<PixelType>, public DestructorInterceptor {
public:
    MockImage(int width, int height) : Image<PixelType>(width, height) {
    }

    MOCK_METHOD3_T(setPixel, void(int, int, PixelType));
    MOCK_METHOD2_T(getPixel, PixelType(int, int));
};

#endif
