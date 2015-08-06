#ifndef WATERSHED_IMPLEMENTATION_HPP
#define WATERSHED_IMPLEMENTATION_HPP

#include <set>
#include <vector>
#include <tuple>

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class WatershedImplementation {
private:
    using DestinationPixel = std::tuple<unsigned int, unsigned int,
            DestinationPixelType>;

    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

public:
    WatershedImplementation(const SourceImageType& source,
            DestinationImageType& destination) : sourceImage(source),
            destinationImage(destination) {
    }

    void apply() {
        DestinationPixelType newestSegment = 0;

        for (auto pixel : getSortedPixels(sourceImage))
            processLevel(pixel, newestSegment, sourceImage, destinationImage);
    }

private:
    std::set<SourcePixelType> getSortedPixels(const SourceImageType& image) {
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        std::set<SourcePixelType> pixels;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                pixels.insert(image.getPixel(x, y));
        }

        return pixels;
    }

    void processLevel(const SourcePixelType& level,
            DestinationPixelType& newestSegment,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        do {
            erodeLevel(level, sourceImage, destinationImage);
        } while (createNewSegment(level, newestSegment, sourceImage,
                    destinationImage));
    }

    void erodeLevel(const SourcePixelType& level,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        std::vector<DestinationPixel> pixelsToUpdate;

        do {
            pixelsToUpdate = collectErosion(level, sourceImage,
                    destinationImage);

            applyErosion(destinationImage, pixelsToUpdate);
        } while (!pixelsToUpdate.empty());
    }

    std::vector<DestinationPixel> collectErosion(const SourcePixelType& level,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();
        std::vector<DestinationPixel> erosionTargets;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                checkErosionCandidate(x, y, level, sourceImage,
                        destinationImage, erosionTargets);
            }
        }

        return erosionTargets;
    }

    void applyErosion(DestinationImageType& image,
            std::vector<DestinationPixel>& pixelsToUpdate) {
        for (auto pixel : pixelsToUpdate) {
            DestinationPixelType value;
            unsigned int x;
            unsigned int y;

            std::tie(x, y, value) = pixel;

            image.setPixel(x, y, value);
        }
    }

    void checkErosionCandidate(unsigned int x, unsigned int y,
            const SourcePixelType& level, const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            std::vector<DestinationPixel>& erosionTargets) {
        if (sourceImage.getPixel(x, y) != level
                || destinationImage.getPixel(x, y) != 0)
            return;

        checkErosionCandidate(x, y, destinationImage, erosionTargets);
    }

    void checkErosionCandidate(unsigned int x, unsigned int y,
            DestinationImageType& image,
            std::vector<DestinationPixel>& erosionTargets) {
        unsigned int maxX = image.getWidth() - 1;
        unsigned int maxY = image.getHeight() - 1;

        if (x > 0 && tryToErodePixel(x, y, x - 1, y, image, erosionTargets))
            return;

        if (y > 0 && tryToErodePixel(x, y, x, y - 1, image, erosionTargets))
            return;

        if (x < maxX && tryToErodePixel(x, y, x + 1, y, image, erosionTargets))
            return;

        if (y < maxY && tryToErodePixel(x, y, x, y + 1, image, erosionTargets))
            return;
    }

    bool tryToErodePixel(unsigned int x, unsigned int y, unsigned int neighborX,
            unsigned int neighborY, DestinationImageType& image,
            std::vector<DestinationPixel>& erosionTargets) {
        auto neighbor = image.getPixel(neighborX, neighborY);

        if (neighbor > 0) {
            erosionTargets.push_back(std::make_tuple(x, y, neighbor));

            return true;
        } else
            return false;
    }

    bool createNewSegment(const SourcePixelType& level,
            DestinationPixelType& newestSegment,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (sourceImage.getPixel(x, y) == level
                        && destinationImage.getPixel(x, y) == 0) {
                    createNewSegmentAt(x, y, newestSegment, destinationImage);

                    return true;
                }
            }
        }

        return false;
    }

    void createNewSegmentAt(unsigned int x, unsigned int y,
            DestinationPixelType& newestSegment, DestinationImageType& image) {
        image.setPixel(x, y, ++newestSegment);
    }
};

#endif
