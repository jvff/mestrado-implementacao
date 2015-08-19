#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <functional>

template <typename PixelType>
class Image {
protected:
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

    unsigned int width;
    unsigned int height;

public:
    Image(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
    }

    virtual ~Image() {
    }

    virtual Image& operator=(const Image<PixelType>& image) {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                setPixel(x, y, image.getPixel(x, y));
        }

        return *this;
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
    virtual PixelType getPixel(unsigned int x, unsigned int y) const = 0;
};

template <typename PixelType>
static bool allPixelsAreEqual(const Image<PixelType>& first,
        const Image<PixelType>& second) {
    unsigned int width = first.getWidth();
    unsigned int height = first.getHeight();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            if (first.getPixel(x, y) != second.getPixel(x, y))
                return false;
        }
    }

    return true;
}

template <typename PixelType>
bool operator==(const Image<PixelType>& first, const Image<PixelType>& second) {
    return first.getWidth() == second.getWidth()
        && first.getHeight() == second.getHeight()
        && allPixelsAreEqual(first, second);
}

#endif
