#ifndef IMAGE_IMPLEMENTATION_TEST_USING_COORDINATES_HPP
#define IMAGE_IMPLEMENTATION_TEST_USING_COORDINATES_HPP

#include "AbstractImageImplementationTest.hpp"

template <typename ImageType, typename PixelType>
class ImageImplementationTestUsingCoordinates
        : public AbstractImageImplementationTest<ImageType, PixelType> {
protected:
    PixelType getPixel(const ImageType& image, unsigned int x, unsigned int y)
            override {
        auto coordinate = Coordinate(x, y);

        return image.getPixelValue(coordinate);
    }

    void setPixel(ImageType& image, unsigned int x, unsigned int y,
            const PixelType& value) override {
        auto coordinate = Coordinate(x, y);

        image.setPixel(coordinate, value);
    }
};

#endif
