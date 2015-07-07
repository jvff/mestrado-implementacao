#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <functional>

template <typename PixelType>
class Image {
protected:
    typedef std::function<PixelType(unsigned int, unsigned int)> PaintFunction;

    unsigned int width;
    unsigned int height;

public:
    Image(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
    }

    virtual ~Image() {
    }

    virtual Image& operator=(PaintFunction makePixel) {
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x)
                setPixel(x, y, makePixel(x, y));
        }

        return *this;
    }

    virtual unsigned int getWidth() const {
        return width;
    }

    virtual unsigned int getHeight() const {
        return height;
    }

    virtual void setPixel(unsigned int x, unsigned int y, PixelType value) = 0;
    virtual PixelType getPixel(unsigned int x, unsigned int y) = 0;
};

#endif
