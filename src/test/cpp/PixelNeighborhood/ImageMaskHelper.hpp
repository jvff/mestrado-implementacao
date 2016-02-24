#ifndef IMAGE_MASK_HELPER_HPP
#define IMAGE_MASK_HELPER_HPP

#include <vector>

#include "SimpleArrayImage.hpp"

class ImageMaskHelper {
private:
    unsigned int width;
    unsigned int height;

public:
    ImageMaskHelper(unsigned int width, unsigned int height)
            : width(width), height(height) {
    }

    std::vector<SimpleArrayImage<bool> > createImageMasks() {
        std::vector<SimpleArrayImage<bool> > imageMasks;

        auto numberOfMasks = getNumberOfMasks();

        for (auto maskId = 0u; maskId < numberOfMasks; ++maskId)
            imageMasks.push_back(createImageMask(maskId));

        return imageMasks;
    }

private:
    unsigned int getNumberOfMasks() {
        return createBitMask(width * height);
    }

    unsigned int createBitMask(unsigned int numberOfBits) {
        return (1u << numberOfBits) - 1;
    }

    SimpleArrayImage<bool> createImageMask(unsigned int maskId) {
        auto imageMask = SimpleArrayImage<bool>(width, height);

        imageMask = [=] (unsigned int x, unsigned int y) -> bool {
            return isPixelSetInMask(maskId, x, y);
        };

        return imageMask;
    }

    bool isPixelSetInMask(unsigned int maskId, unsigned int x, unsigned int y) {
        auto coordinateBitIndex = getPixelIndex(x, y);

        return isBitSet(coordinateBitIndex, maskId);
    }

    unsigned int getPixelIndex(unsigned int x, unsigned int y) {
        return x + y * width;
    }

    bool isBitSet(unsigned int bitIndex, unsigned int bits) {
        auto bitMask = createMaskForBit(bitIndex);

        return (bits & bitMask) != 0;
    }

    unsigned int createMaskForBit(unsigned int bitIndex) {
        return 1u << bitIndex;
    }
};

#endif
