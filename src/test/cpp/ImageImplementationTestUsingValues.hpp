#ifndef IMAGE_IMPLEMENTATION_TEST_USING_VALUES_HPP
#define IMAGE_IMPLEMENTATION_TEST_USING_VALUES_HPP

#include "AbstractImageImplementationTest.hpp"

template <typename ImageType, typename PixelType>
class ImageImplementationTestUsingValues
        : public AbstractImageImplementationTest<ImageType, PixelType> {
protected:
    PixelType getPixel(const ImageType& image, unsigned int x, unsigned int y)
            override {
        return image.getPixelValue(x, y);
    }

    void setPixel(ImageType& image, unsigned int x, unsigned int y,
            const PixelType& value) override {
        image.setPixel(x, y, value);
    }
};

#endif
