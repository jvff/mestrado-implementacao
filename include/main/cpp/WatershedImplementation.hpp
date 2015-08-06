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

    unsigned int width;
    unsigned int height;

public:
    WatershedImplementation(const SourceImageType& source,
            DestinationImageType& destination) : sourceImage(source),
            destinationImage(destination), width(sourceImage.getWidth()),
            height(sourceImage.getHeight()) {
    }

    void apply() {
        DestinationPixelType newestSegment = 0;

        for (auto pixel : getSortedPixels())
            processLevel(pixel, newestSegment);
    }

private:
    std::set<SourcePixelType> getSortedPixels() {
        std::set<SourcePixelType> pixels;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                pixels.insert(sourceImage.getPixel(x, y));
        }

        return pixels;
    }

    void processLevel(const SourcePixelType& level,
            DestinationPixelType& newestSegment) {
        do {
            erodeLevel(level);
        } while (createNewSegment(level, newestSegment));
    }

    void erodeLevel(const SourcePixelType& level) {
        std::vector<DestinationPixel> pixelsToUpdate;

        do {
            pixelsToUpdate = collectErosion(level);

            applyErosion(pixelsToUpdate);
        } while (!pixelsToUpdate.empty());
    }

    std::vector<DestinationPixel> collectErosion(const SourcePixelType& level) {
        std::vector<DestinationPixel> erosionTargets;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkErosionCandidate(x, y, level, erosionTargets);
        }

        return erosionTargets;
    }

    void applyErosion(std::vector<DestinationPixel>& pixelsToUpdate) {
        for (auto pixel : pixelsToUpdate) {
            DestinationPixelType value;
            unsigned int x;
            unsigned int y;

            std::tie(x, y, value) = pixel;

            destinationImage.setPixel(x, y, value);
        }
    }

    void checkErosionCandidate(unsigned int x, unsigned int y,
            const SourcePixelType& level,
            std::vector<DestinationPixel>& erosionTargets) {
        if (sourceImage.getPixel(x, y) != level
                || destinationImage.getPixel(x, y) != 0)
            return;

        checkErosionCandidate(x, y, erosionTargets);
    }

    void checkErosionCandidate(unsigned int x, unsigned int y,
            std::vector<DestinationPixel>& erosionTargets) {
        unsigned int maxX = destinationImage.getWidth() - 1;
        unsigned int maxY = destinationImage.getHeight() - 1;

        if (x > 0 && tryToErodePixel(x, y, x - 1, y, erosionTargets))
            return;

        if (y > 0 && tryToErodePixel(x, y, x, y - 1, erosionTargets))
            return;

        if (x < maxX && tryToErodePixel(x, y, x + 1, y, erosionTargets))
            return;

        if (y < maxY && tryToErodePixel(x, y, x, y + 1, erosionTargets))
            return;
    }

    bool tryToErodePixel(unsigned int x, unsigned int y, unsigned int neighborX,
            unsigned int neighborY,
            std::vector<DestinationPixel>& erosionTargets) {
        auto neighbor = destinationImage.getPixel(neighborX, neighborY);

        if (neighbor > 0) {
            erosionTargets.push_back(std::make_tuple(x, y, neighbor));

            return true;
        } else
            return false;
    }

    bool createNewSegment(const SourcePixelType& level,
            DestinationPixelType& newestSegment) {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (sourceImage.getPixel(x, y) == level
                        && destinationImage.getPixel(x, y) == 0) {
                    createNewSegmentAt(x, y, newestSegment);

                    return true;
                }
            }
        }

        return false;
    }

    void createNewSegmentAt(unsigned int x, unsigned int y,
            DestinationPixelType& newestSegment) {
        destinationImage.setPixel(x, y, ++newestSegment);
    }
};

#endif
