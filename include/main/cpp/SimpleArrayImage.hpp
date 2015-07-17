#ifndef SIMPLE_ARRAY_IMAGE_HPP
#define SIMPLE_ARRAY_IMAGE_HPP

#include "Image.hpp"

template <typename PixelType>
class SimpleArrayImage : public Image<PixelType> {
private:
    PixelType* pixels;

    inline unsigned int getPixelIndex(unsigned int x, unsigned int y) const {
        return y * Image<PixelType>::width + x;
    }

public:
    SimpleArrayImage(unsigned int width, unsigned int height)
            : Image<PixelType>(width, height) {
        pixels = new PixelType[width * height];
    }

    virtual ~SimpleArrayImage() {
        delete[] pixels;
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) {
        pixels[getPixelIndex(x, y)] = value;
    }

    PixelType getPixel(unsigned int x, unsigned int y) const {
        return pixels[getPixelIndex(x, y)];
    }
};

template <>
class SimpleArrayImage<bool> : public Image<bool> {
private:
    unsigned int pixelsPerBlock;
    long* blocks;

    inline unsigned int getPixelIndex(unsigned int x, unsigned int y) const {
        return y * width + x;
    }

    inline unsigned int getBlockIndex(unsigned int pixelIndex) const {
        return pixelIndex / pixelsPerBlock;
    }

    inline long getPixelMask(unsigned int pixelIndex) const {
        unsigned int pixelIndexInBlock = pixelIndex % pixelsPerBlock;

        return 1 << pixelIndexInBlock;
    }
public:
    SimpleArrayImage(unsigned int width, unsigned int height)
            : Image(width, height) {
        unsigned int totalPixels = width * height;

        pixelsPerBlock = sizeof(long) * 8;
        blocks = new long[(totalPixels - 1) / pixelsPerBlock + 1];
    }

    ~SimpleArrayImage() {
        delete[] blocks;
    }

    virtual void setPixel(unsigned int x, unsigned int y, bool value) {
        unsigned int pixelIndex = getPixelIndex(x, y);
        unsigned int blockIndex = getBlockIndex(pixelIndex);
        long mask = getPixelMask(pixelIndex);
        long invertedMask = ~mask;

        if (value == true)
            blocks[blockIndex] |= mask;
        else
            blocks[blockIndex] &= invertedMask;
    }

    virtual bool getPixel(unsigned int x, unsigned int y) const {
        unsigned int pixelIndex = getPixelIndex(x, y);
        unsigned int blockIndex = getBlockIndex(pixelIndex);
        long mask = getPixelMask(pixelIndex);

        return (blocks[blockIndex] & mask) != 0L;
    }
};

#endif
