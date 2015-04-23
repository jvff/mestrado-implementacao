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

    virtual ~SimpleArrayImage() {
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
    long* blocks;

    inline int getPixelIndex(int x, int y) {
	return y * width + x;
    }

    inline int getBlockIndex(int pixelIndex) {
	return pixelIndex / pixelsPerBlock;
    }

    inline long getPixelMask(int pixelIndex) {
	int pixelIndexInBlock = pixelIndex % pixelsPerBlock;

	return 1 << pixelIndexInBlock;
    }
public:
    SimpleArrayImage(int width, int height) : Image(width, height) {
	int totalPixels = width * height;

	pixelsPerBlock = sizeof(long) * 8;
	blocks = new long[(totalPixels - 1) / pixelsPerBlock + 1];
    }

    ~SimpleArrayImage() {
	delete[] blocks;
    }

    virtual void setPixel(int x, int y, bool value) {
	int pixelIndex = getPixelIndex(x, y);
	int blockIndex = getBlockIndex(pixelIndex);
	long mask = getPixelMask(pixelIndex);
	long invertedMask = ~mask;

	if (value == true)
	    blocks[blockIndex] |= mask;
	else
	    blocks[blockIndex] &= invertedMask;
    }

    virtual bool getPixel(int x, int y) {
	int pixelIndex = getPixelIndex(x, y);
	int blockIndex = getBlockIndex(pixelIndex);
	long mask = getPixelMask(pixelIndex);

	return (blocks[blockIndex] & mask) != 0L;
    }
};

#endif
