#ifndef WATERSHED_IMPLEMENTATION_HPP
#define WATERSHED_IMPLEMENTATION_HPP

#include <map>
#include <set>
#include <tuple>

#include "FilterImplementation.hpp"
#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType>
class WatershedImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using Coordinate = std::pair<unsigned int, unsigned int>;
    using SourcePixelType = typename SourceImageType::PixelType;
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::maxX;
    using SuperClass::maxY;

    SourcePixelType currentLevel;
    DestinationPixelType newestSegment;

    std::map<Coordinate, DestinationPixelType> erosionMap;
    std::set<Coordinate> currentSeparators;

public:
    WatershedImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage), newestSegment(0) {
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
                levels.insert(sourceImage.getPixelValue(x, y));
        }

        return levels;
    }

    void processLevel(const SourcePixelType& level) {
        currentLevel = level;
        currentSeparators.clear();

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
            DestinationPixelType value = pixel.second;
            unsigned int x, y;

            std::tie(x, y) = pixel.first;

            destinationImage.setPixel(x, y, value);
        }
    }

    void checkErosionCandidate(unsigned int x, unsigned int y) {
        if (pixelShouldBeProcessed(x, y)) {
            checkErosionCandidate(x, y, x > 0, x - 1, y)
                || checkErosionCandidate(x, y, y > 0, x, y - 1)
                || checkErosionCandidate(x, y, x < maxX, x + 1, y)
                || checkErosionCandidate(x, y, y < maxY, x, y + 1);
        }
    }

    bool checkErosionCandidate(unsigned int x, unsigned int y,
            bool precondition, unsigned int neighborX, unsigned int neighborY) {
        if (precondition == false)
            return false;
        else
            return tryToErodePixel(x, y, neighborX, neighborY);
    }

    bool tryToErodePixel(unsigned int x, unsigned int y, unsigned int neighborX,
            unsigned int neighborY) {
        auto neighbor = destinationImage.getPixelValue(neighborX, neighborY);

        if (neighbor > 0) {
            auto coordinate = std::make_pair(x, y);
            auto previousErosion = erosionMap.find(coordinate);
            auto notFound = erosionMap.end();

            if (previousErosion == notFound)
                erosionMap[coordinate] = neighbor;
            else if (erosionMap[coordinate] != neighbor) {
                erosionMap.erase(previousErosion);
                currentSeparators.insert(coordinate);

                return true;
            }
        }

        return false;
    }

    bool tryToCreateNewSegment() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (shouldCreateNewSegmentAt(x, y)) {
                    createNewSegmentAt(x, y);

                    return true;
                }
            }
        }

        return false;
    }

    bool shouldCreateNewSegmentAt(unsigned int x, unsigned int y) {
        return pixelShouldBeProcessed(x, y) && pixelIsntSeparator(x, y)
            && pixelIsntSurroundedBySeparators(x, y);
    }

    void createNewSegmentAt(unsigned int x, unsigned int y) {
        destinationImage.setPixel(x, y, ++newestSegment);
    }

    bool pixelShouldBeProcessed(unsigned int x, unsigned int y) {
        return pixelIsAtCurrentLevel(x, y) && pixelHasntBeenSetYet(x, y);
    }

    bool pixelIsAtCurrentLevel(unsigned int x, unsigned int y) {
        return sourceImage.getPixelValue(x, y) == currentLevel;
    }

    bool pixelHasntBeenSetYet(unsigned int x, unsigned int y) {
        return destinationImage.getPixelValue(x, y) == 0;
    }

    bool pixelIsntSeparator(unsigned int x, unsigned int y) {
        return pixelIsntCurrentSeparator(x, y) && pixelIsntOldSeparator(x, y);
    }

    bool pixelIsntCurrentSeparator(unsigned int x, unsigned int y) {
        auto coordinate = std::make_pair(x, y);
        auto notFound = currentSeparators.end();

        return currentSeparators.find(coordinate) == notFound;
    }

    bool pixelIsntOldSeparator(unsigned int x, unsigned int y) {
        auto level = sourceImage.getPixelValue(x, y);
        auto pixelValue = destinationImage.getPixelValue(x, y);
        auto separatorValue = 0;

        return !(level < currentLevel && pixelValue != separatorValue);
    }

    bool pixelIsntSurroundedBySeparators(unsigned int x, unsigned int y) {
        return neighborIsntSeparator(x > 0, x - 1, y)
            || neighborIsntSeparator(y > 0, x, y - 1)
            || neighborIsntSeparator(x < maxX, x + 1, y)
            || neighborIsntSeparator(y < maxY, x, y + 1);
    }

    bool neighborIsntSeparator(bool neighborExists, unsigned int x,
            unsigned int y) {
        return neighborExists && pixelIsntSeparator(x, y);
    }
};

#endif
