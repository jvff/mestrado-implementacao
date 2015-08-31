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

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

public:
    MorphologicalReconstructionImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
        std::queue<Pixel> pixelsToBeUpdated;

        avoidMarkersBiggerThanSourcePixels(sourceImage, destinationImage);
        firstPass(sourceImage, destinationImage);
        secondPass(sourceImage, destinationImage, pixelsToBeUpdated);
        thirdPass(sourceImage, destinationImage, pixelsToBeUpdated);
    }

private:
    void avoidMarkersBiggerThanSourcePixels(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                const PixelType sourcePixel = sourceImage.getPixel(x, y);
                const PixelType markerPixel = destinationImage.getPixel(x, y);
                const PixelType truncatedMarkerPixel =
                        std::min(markerPixel, sourcePixel);

                destinationImage.setPixel(x, y, truncatedMarkerPixel);
            }
        }
    }

    void firstPass(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        for (unsigned int x = 0; x < maxX; ++x) {
            for (unsigned int y = 0; y < maxY; ++y) {
                propagateRight(sourceImage, destinationImage, x, y);
                propagateDown(sourceImage, destinationImage, x, y);
            }
        }

        propagateRight(sourceImage, destinationImage, maxX - 1, maxY);
        propagateDown(sourceImage, destinationImage, maxX, maxY - 1);
    }

    void secondPass(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            std::queue<Pixel>& pixelsToBeUpdated) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        for (unsigned int x = maxX; x > 0; --x) {
            for (unsigned int y = maxY; y > 0; --y) {
                if (propagateLeft(sourceImage, destinationImage, x, y))
                    pixelsToBeUpdated.push(std::make_tuple(x - 1, y));

                if (propagateUp(sourceImage, destinationImage, x, y))
                    pixelsToBeUpdated.push(std::make_tuple(x, y - 1));
            }
        }
    }

    void thirdPass(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            std::queue<Pixel>& pixelsToBeUpdated) {
        unsigned int x, y;

        while (!pixelsToBeUpdated.empty()) {
            std::tie(x, y) = pixelsToBeUpdated.front();

            if (propagateLeft(sourceImage, destinationImage, x, y))
                pixelsToBeUpdated.push(std::make_tuple(x - 1, y));

            if (propagateRight(sourceImage, destinationImage, x, y))
                pixelsToBeUpdated.push(std::make_tuple(x + 1, y));

            if (propagateUp(sourceImage, destinationImage, x, y))
                pixelsToBeUpdated.push(std::make_tuple(x, y - 1));

            if (propagateDown(sourceImage, destinationImage, x, y))
                pixelsToBeUpdated.push(std::make_tuple(x, y + 1));

            pixelsToBeUpdated.pop();
        }
    }

    bool propagateRight(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        return propagatePixel(sourceImage, destinationImage, x, y, x + 1, y);
    }

    bool propagateDown(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        return propagatePixel(sourceImage, destinationImage, x, y, x, y + 1);
    }

    bool propagateLeft(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        return propagatePixel(sourceImage, destinationImage, x, y, x - 1, y);
    }

    bool propagateUp(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        return propagatePixel(sourceImage, destinationImage, x, y, x, y - 1);
    }

    bool propagatePixel(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y, unsigned int nextX, unsigned int nextY) {
        if (coordinateIsInvalid(sourceImage, nextX, nextY))
            return false;

        const PixelType markerCurrent = destinationImage.getPixel(x, y);
        const PixelType markerNext = destinationImage.getPixel(nextX, nextY);
        const PixelType sourcePixel = sourceImage.getPixel(nextX, nextY);

        const PixelType propagatedPixel = std::min(markerCurrent, sourcePixel);
        const PixelType destinationPixel = std::max(propagatedPixel,
                markerNext);

        destinationImage.setPixel(nextX, nextY, destinationPixel);

        return markerNext != destinationPixel;
    }

    bool coordinateIsInvalid(const SourceImageType& sourceImage, unsigned int x,
            unsigned int y) {
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        return x > maxX || y > maxY;
    }
};

#endif
