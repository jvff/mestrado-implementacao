#ifndef SIMPLE_ARRAY_IMAGE_HPP
#define SIMPLE_ARRAY_IMAGE_HPP

#include "Image.hpp"

template <typename PixelType>
class SimpleArrayImage : public Image<PixelType> {
private:
    PixelType* pixels;

    inline int getPixelIndex(int x, int y) {
        return y * Image<PixelType>::width + x;
    }

public:
    SimpleArrayImage(int width, int height) : Image<PixelType>(width, height) {
        pixels = new PixelType[width * height];
    }

    ~SimpleArrayImage() {
        delete[] pixels;
    }

    void setPixel(int x, int y, PixelType value) {
        pixels[getPixelIndex(x, y)] = value;
    }

    PixelType getPixel(int x, int y) {
        return pixels[getPixelIndex(x, y)];
    }
};

template <>
class SimpleArrayImage<bool> : public Image<bool> {
private:
    int pixelsPerBlock;
    int blockWidth;
    long* blocks;

    inline int getBlockIndex(int x, int y) {
	return y * blockWidth + x / pixelsPerBlock;
    }

    inline long getPixelMask(int x) {
	int pixelIndex = x % pixelsPerBlock;

	return 1 << pixelIndex;
    }
public:
    SimpleArrayImage(int width, int height) : Image(width, height) {
	pixelsPerBlock = sizeof(long) * 8;
	blockWidth = width / pixelsPerBlock + 1;
	blocks = new long[blockWidth * height];
    }

    ~SimpleArrayImage() {
	delete[] blocks;
    }

    virtual void setPixel(int x, int y, bool value) {
	int index = getBlockIndex(x, y);
	long mask = getPixelMask(x);
	long invertedMask = ~mask;

	if (value == true)
	    blocks[index] |= mask;
	else
	    blocks[index] &= invertedMask;
    }

    virtual bool getPixel(int x, int y) {
	return (blocks[getBlockIndex(x, y)] & getPixelMask(x)) != 0L;
    }
};

#endif
