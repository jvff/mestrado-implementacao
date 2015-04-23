#ifndef IMAGE_HPP
#define IMAGE_HPP

template <typename PixelType>
class Image {
protected:
    int width;
    int height;

public:
    Image(int width, int height) {
        this->width = width;
        this->height = height;
    }

    virtual ~Image() {
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    virtual void setPixel(int x, int y, PixelType value) = 0;
    virtual PixelType getPixel(int x, int y) = 0;
};

#endif
