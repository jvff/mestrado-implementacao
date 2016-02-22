#ifndef IMAGE_MASK_HELPER_HPP
#define IMAGE_MASK_HELPER_HPP

#include <functional>
#include <vector>

#include "Image.hpp"
#include "SimpleArrayImage.hpp"

class ImageMaskHelper {
private:
    using ImageMaskFilter = std::function<bool(const Image<bool>&)>;

    unsigned int width;
    unsigned int height;

public:
    ImageMaskHelper(unsigned int width, unsigned int height)
            : width(width), height(height) {
    }

    std::vector<SimpleArrayImage<bool> > createImageMasks() {
        auto includeAllMasks = [] (const Image<bool>&) {
            return true;
        };

        return createImageMasks(includeAllMasks);
    }

    std::vector<SimpleArrayImage<bool> > createImageMasks(
            ImageMaskFilter shouldIncludeMask) {
        std::vector<SimpleArrayImage<bool> > imageMasks;

        auto numberOfMasks = getNumberOfMasks();

        imageMasks.reserve(numberOfMasks);

        for (auto maskId = 0u; maskId < numberOfMasks; ++maskId)
            maybeAddNewMask(imageMasks, maskId, shouldIncludeMask);

        return imageMasks;
    }

public:
    static bool doesPixelHaveAvailableNeighbor(const Image<bool>& image,
            unsigned int x, unsigned int y) {
        auto maxX = image.getWidth() - 1;
        auto maxY = image.getHeight() - 1;

        return neighborIsAvailable(image, x > 0, x - 1, y)
            || neighborIsAvailable(image, y > 0, x, y - 1)
            || neighborIsAvailable(image, x < maxX, x + 1, y)
            || neighborIsAvailable(image, y < maxY, x, y + 1);
    }

    static bool imageMaskHasAvailableNeighborForAllPixels(const Image<bool>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                if (doesPixelHaveAvailableNeighbor(image, x, y) == false)
                    return false;
            }
        }

        return true;
    }

private:
    unsigned int getNumberOfMasks() {
        return createBitMask(width * height);
    }

    unsigned int createBitMask(unsigned int numberOfBits) {
        return (1u << numberOfBits) - 1;
    }

    void maybeAddNewMask(std::vector<SimpleArrayImage<bool> >& imageMasks,
            unsigned int maskId, ImageMaskFilter shouldIncludeMask) {
        auto imageMask = createImageMask(maskId);

        if (shouldIncludeMask(imageMask))
            imageMasks.push_back(imageMask);
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

private:
    static bool neighborIsAvailable(const Image<bool>& image,
            bool coordinateIsValid, unsigned int x, unsigned int y) {
        return coordinateIsValid && pixelIsNotMarked(image, x, y);
    }

    static bool pixelIsNotMarked(const Image<bool>& image, unsigned int x,
            unsigned int y) {
        return !image.getPixelValue(x, y);
    }
};

#endif
