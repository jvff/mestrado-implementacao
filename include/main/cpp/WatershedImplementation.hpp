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

    SourcePixelType currentLevel;
    DestinationPixelType newestSegment;

    unsigned int width;
    unsigned int height;

    std::vector<DestinationPixel> erosionTargets;

public:
    WatershedImplementation(const SourceImageType& source,
            DestinationImageType& destination) : sourceImage(source),
            destinationImage(destination), newestSegment(0),
            width(sourceImage.getWidth()), height(sourceImage.getHeight()) {
    }

    void apply() {
        for (auto pixel : getSortedPixels())
            processLevel(pixel);
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

    void processLevel(const SourcePixelType& level) {
        currentLevel = level;

        do {
            erodeLevel();
        } while (createNewSegment());
    }

    void erodeLevel() {
        do {
            collectErosion();
            applyErosion();
        } while (!erosionTargets.empty());
    }

    void collectErosion() {
        erosionTargets.clear();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkErosionCandidate(x, y);
        }
    }

    void applyErosion() {
        for (auto pixel : erosionTargets) {
            DestinationPixelType value;
            unsigned int x;
            unsigned int y;

            std::tie(x, y, value) = pixel;

            destinationImage.setPixel(x, y, value);
        }
    }

    void checkErosionCandidate(unsigned int x, unsigned int y) {
        if (sourceImage.getPixel(x, y) != currentLevel
                || destinationImage.getPixel(x, y) != 0)
            return;

        unsigned int maxX = destinationImage.getWidth() - 1;
        unsigned int maxY = destinationImage.getHeight() - 1;

        if (x > 0 && tryToErodePixel(x, y, x - 1, y))
            return;

        if (y > 0 && tryToErodePixel(x, y, x, y - 1))
            return;

        if (x < maxX && tryToErodePixel(x, y, x + 1, y))
            return;

        if (y < maxY && tryToErodePixel(x, y, x, y + 1))
            return;
    }

    bool tryToErodePixel(unsigned int x, unsigned int y, unsigned int neighborX,
            unsigned int neighborY) {
        auto neighbor = destinationImage.getPixel(neighborX, neighborY);

        if (neighbor > 0) {
            erosionTargets.push_back(std::make_tuple(x, y, neighbor));

            return true;
        } else
            return false;
    }

    bool createNewSegment() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (sourceImage.getPixel(x, y) == currentLevel
                        && destinationImage.getPixel(x, y) == 0) {
                    createNewSegmentAt(x, y);

                    return true;
                }
            }
        }

        return false;
    }

    void createNewSegmentAt(unsigned int x, unsigned int y) {
        destinationImage.setPixel(x, y, ++newestSegment);
    }
};

#endif
