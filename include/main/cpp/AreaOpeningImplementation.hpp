#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include <functional>
#include <set>

#include "Coordinate.hpp"
#include "FilterImplementation.hpp"
#include "Image.hpp"
#include "Pixel.hpp"
#include "RegionalMaximumsFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using DestinationPixel = Pixel<DestinationPixelType>;
    using AscendingPixelComparator =
            typename DestinationPixel::AscendingComparator;
    using DescendingPixelComparator =
            typename DestinationPixel::DescendingComparator;
    using RegionalMaximumsFilterType = RegionalMaximumsFilter<SourceImageType,
            DestinationImageType>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    Coordinate noPeaksFound;
    Coordinate startOfPeak;
    DestinationPixelType peakValue;

    RegionalMaximumsFilterType regionalMaximumsFilter;
    DestinationImageType regionalMaximums;

    std::set<DestinationPixel, DescendingPixelComparator> pixelsToCheck;
    std::set<DestinationPixel, AscendingPixelComparator> pixelsToUpdate;

    unsigned int maximumPeakSize;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::maxX;
    using SuperClass::maxY;

public:
    AreaOpeningImplementation(unsigned int maximumPeakSize,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            noPeaksFound(width, height), regionalMaximums(width, height),
            maximumPeakSize(maximumPeakSize) {
    }

    void apply() {
        copySourceImage();
        findRegionalMaximums();
        clearPeaks();
    }

private:
    void copySourceImage() {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            return sourceImage.getPixelValue(x, y);
        };
    }

    void findRegionalMaximums() {
        regionalMaximums = regionalMaximumsFilter.apply(sourceImage);
    }

    void clearPeaks() {
        startOfPeak = findStartOfPeak();

        while (startOfPeak != noPeaksFound) {
            maybeClearPeak();
            startOfPeak = findStartOfPeak();
        }
    }

    Coordinate findStartOfPeak() {
        for (unsigned int x = 0; x < width; x++) {
            for (unsigned int y = 0; y < height; y++) {
                if (regionalMaximums.getPixelValue(x, y) > 0) {
                    peakValue = destinationImage.getPixelValue(x, y);
                    return Coordinate(x, y);
                }
            }
        }

        return noPeaksFound;
    }

    void maybeClearPeak() {
        pixelsToUpdate.clear();
        pixelsToCheck.clear();

        pixelsToCheck.insert(pixelAt(startOfPeak));

        collectPixelsToUpdate();
        clearPixels();
    }

    void collectPixelsToUpdate() {
        DestinationPixelType currentLevel = peakValue;
        DestinationPixelType level = peakValue;

        while (thereAreMorePixelsToCollect() && level <= currentLevel) {
            auto firstPosition = pixelsToCheck.begin();
            auto pixel = *firstPosition;

            pixelsToCheck.erase(firstPosition);

            currentLevel = level;
            level = pixel.value;

            if (level <= currentLevel)
                collectPixel(pixel);
        }
    }

    void clearPixels() {
        auto value = getValueToClearPixels();

        for (auto pixel : pixelsToUpdate)
            updatePixel(pixel, value);
    }

    bool thereAreMorePixelsToCollect() {
        return haventCollectedEnoughPixels() && moreNeighborsAreAvailable();
    }

    bool haventCollectedEnoughPixels() {
        return pixelsToUpdate.size() < maximumPeakSize;
    }

    bool moreNeighborsAreAvailable() {
        return !pixelsToCheck.empty();
    }

    void collectPixel(const DestinationPixel& pixel) {
        pixelsToUpdate.insert(pixel);
        queueNeighbors(pixel);
    }

    void queueNeighbors(const DestinationPixel& pixel) {
        const auto x = pixel.x;
        const auto y = pixel.y;

        maybeQueueNeighbor(x < maxX, x + 1, y);
        maybeQueueNeighbor(y < maxY, x, y + 1);
        maybeQueueNeighbor(x > 0, x - 1, y);
        maybeQueueNeighbor(y > 0, x, y - 1);
    }

    void maybeQueueNeighbor(bool precondition, unsigned int x, unsigned int y) {
        if (precondition)
            maybeQueuePixel(pixelAt(x, y));
    }

    void maybeQueuePixel(const DestinationPixel& pixel) {
        if (pixelHasntBeenProcessed(pixel))
            pixelsToCheck.insert(pixel);
    }

    bool pixelHasntBeenProcessed(const DestinationPixel& pixel) {
        auto notFound = pixelsToUpdate.end();

        return pixelsToUpdate.find(pixel) == notFound;
    }

    DestinationPixelType getValueToClearPixels() {
        auto firstPosition = pixelsToUpdate.begin();
        auto pixel = *firstPosition;

        return pixel.value;
    }

    void updatePixel(const DestinationPixel& pixel,
            const DestinationPixelType& value) {
        destinationImage.setPixel(pixel.x, pixel.y, value);
        regionalMaximums.setPixel(pixel.x, pixel.y, 0);
    }

    DestinationPixel pixelAt(const Coordinate& coordinate) {
        return destinationImage.getPixel(coordinate);
    }

    DestinationPixel pixelAt(unsigned int x, unsigned int y) {
        return destinationImage.getPixel(x, y);
    }
};

#endif
