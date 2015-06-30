#ifndef IMAGE_HPP
#define IMAGE_HPP

template <typename PixelType>
class Image {
protected:
    unsigned int width;
    unsigned int height;

public:
    Image(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
    }

    virtual ~Image() {
    }

    virtual unsigned int getWidth() const {
        return width;
    }

    virtual unsigned int getHeight() {
        return height;
    }

    virtual void setPixel(unsigned int x, unsigned int y, PixelType value) = 0;
    virtual PixelType getPixel(unsigned int x, unsigned int y) = 0;
};

#endif
