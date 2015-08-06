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
    unsigned int maxX;
    unsigned int maxY;

    std::vector<DestinationPixel> erosionMap;

public:
    WatershedImplementation(const SourceImageType& source,
            DestinationImageType& destination) : sourceImage(source),
            destinationImage(destination), newestSegment(0),
            width(sourceImage.getWidth()), height(sourceImage.getHeight()),
            maxX(width - 1), maxY(height - 1) {
    }

    void apply() {
        for (auto pixel : getSortedLevels())
            processLevel(pixel);
    }

private:
    std::set<SourcePixelType> getSortedLevels() {
        std::set<SourcePixelType> levels;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                levels.insert(sourceImage.getPixel(x, y));
        }

        return levels;
    }

    void processLevel(const SourcePixelType& level) {
        currentLevel = level;

        do {
            erodeLevel();
        } while (tryToCreateNewSegment());
    }

    void erodeLevel() {
        do {
            collectErosion();
            applyErosion();
        } while (!erosionMap.empty());
    }

    void collectErosion() {
        erosionMap.clear();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkErosionCandidate(x, y);
        }
    }

    void applyErosion() {
        for (auto pixel : erosionMap) {
            DestinationPixelType value;
            unsigned int x;
            unsigned int y;

            std::tie(x, y, value) = pixel;

            destinationImage.setPixel(x, y, value);
        }
    }

    void checkErosionCandidate(unsigned int x, unsigned int y) {
        if (!pixelShouldBeProcessed(x, y))
            return;

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
            erosionMap.push_back(std::make_tuple(x, y, neighbor));

            return true;
        } else
            return false;
    }

    bool tryToCreateNewSegment() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (pixelShouldBeProcessed(x, y)) {
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

    bool pixelShouldBeProcessed(unsigned int x, unsigned int y) {
        return pixelIsAtCurrentLevel(x, y) && pixelHasntBeenSetYet(x, y);
    }

    bool pixelIsAtCurrentLevel(unsigned int x, unsigned int y) {
        return sourceImage.getPixel(x, y) == currentLevel;
    }

    bool pixelHasntBeenSetYet(unsigned int x, unsigned int y) {
        return destinationImage.getPixel(x, y) == 0;
    }
};

#endif
