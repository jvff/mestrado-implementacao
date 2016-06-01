#ifndef IMAGE_IMPLEMENTATION_TEST_USING_PIXELS_HPP
#define IMAGE_IMPLEMENTATION_TEST_USING_PIXELS_HPP

#include "ImageImplementationTestUsingCoordinates.hpp"

template <typename ImageType, typename PixelType>
class ImageImplementationTestUsingPixels
        : public ImageImplementationTestUsingCoordinates<ImageType, PixelType> {
protected:
    void setPixel(ImageType& image, unsigned int x, unsigned int y,
            const PixelType& value) override {
        auto pixel = Pixel<PixelType>(x, y, value);

        image.setPixel(pixel);
    }
};

#endif
