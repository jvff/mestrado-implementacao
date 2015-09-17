#ifndef MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP

#include <queue>
#include <tuple>

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class MorphologicalReconstructionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using Pixel = std::tuple<unsigned int, unsigned int>;
    using PixelType = typename DestinationImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    std::queue<Pixel> pixelsToBeUpdated;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::maxX;
    using SuperClass::maxY;

public:
    MorphologicalReconstructionImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
        avoidMarkersBiggerThanSourcePixels();
        firstPass();
        secondPass();
        thirdPass();
    }

private:
    void avoidMarkersBiggerThanSourcePixels() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                const auto sourcePixel = sourceImage.getPixelValue(x, y);
                const auto markerPixel = destinationImage.getPixelValue(x, y);
                const auto truncatedMarkerPixel =
                        std::min(markerPixel, sourcePixel);

                destinationImage.setPixel(x, y, truncatedMarkerPixel);
            }
        }
    }

    void firstPass() {
        for (unsigned int x = 0; x < maxX; ++x) {
            for (unsigned int y = 0; y < maxY; ++y) {
                propagateRight(x, y);
                propagateDown(x, y);
            }
        }

        propagateRight(maxX - 1, maxY);
        propagateDown(maxX, maxY - 1);
    }

    void secondPass() {
        for (unsigned int x = maxX; x > 0; --x) {
            for (unsigned int y = maxY; y > 0; --y) {
                if (propagateLeft(x, y))
                    pixelsToBeUpdated.push(std::make_tuple(x - 1, y));

                if (propagateUp(x, y))
                    pixelsToBeUpdated.push(std::make_tuple(x, y - 1));
            }
        }
    }

    void thirdPass() {
        unsigned int x, y;

        while (!pixelsToBeUpdated.empty()) {
            std::tie(x, y) = pixelsToBeUpdated.front();

            if (propagateLeft(x, y))
                pixelsToBeUpdated.push(std::make_tuple(x - 1, y));

            if (propagateRight(x, y))
                pixelsToBeUpdated.push(std::make_tuple(x + 1, y));

            if (propagateUp(x, y))
                pixelsToBeUpdated.push(std::make_tuple(x, y - 1));

            if (propagateDown(x, y))
                pixelsToBeUpdated.push(std::make_tuple(x, y + 1));

            pixelsToBeUpdated.pop();
        }
    }

    bool propagateRight(unsigned int x, unsigned int y) {
        return propagatePixel(x, y, x + 1, y);
    }

    bool propagateDown(unsigned int x, unsigned int y) {
        return propagatePixel(x, y, x, y + 1);
    }

    bool propagateLeft(unsigned int x, unsigned int y) {
        return propagatePixel(x, y, x - 1, y);
    }

    bool propagateUp(unsigned int x, unsigned int y) {
        return propagatePixel(x, y, x, y - 1);
    }

    bool propagatePixel(unsigned int x, unsigned int y, unsigned int nextX,
            unsigned int nextY) {
        if (coordinateIsInvalid(nextX, nextY))
            return false;

        const auto markerCurrent = destinationImage.getPixelValue(x, y);
        const auto markerNext = destinationImage.getPixelValue(nextX, nextY);
        const auto sourcePixel = sourceImage.getPixelValue(nextX, nextY);

        const auto propagatedPixel = std::min(markerCurrent, sourcePixel);
        const auto destinationPixel = std::max(propagatedPixel, markerNext);

        destinationImage.setPixel(nextX, nextY, destinationPixel);

        return markerNext != destinationPixel;
    }

    bool coordinateIsInvalid(unsigned int x, unsigned int y) {
        return x > maxX || y > maxY;
    }
};

#endif
