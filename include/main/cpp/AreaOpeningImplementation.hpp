#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include <functional>
#include <set>

#include "FilterImplementation.hpp"
#include "Image.hpp"
#include "RegionalMaximumsFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using Coordinate = std::pair<unsigned int, unsigned int>;
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using Pixel = std::tuple<DestinationPixelType, unsigned int, unsigned int>;
    using RegionalMaximumsFilterType = RegionalMaximumsFilter<SourceImageType,
            DestinationImageType>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    Coordinate noPeaksFound;

    RegionalMaximumsFilterType regionalMaximumsFilter;
    DestinationImageType regionalMaximums;

    std::set<Pixel, std::greater<Pixel> > pixelsToCheck;
    std::set<Pixel> pixelsToUpdate;

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
            noPeaksFound(std::make_pair(width, height)),
            regionalMaximums(width, height),
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
            return sourceImage.getPixel(x, y);
        };
    }

    void findRegionalMaximums() {
        regionalMaximums = regionalMaximumsFilter.apply(sourceImage);
    }

    void clearPeaks() {
        auto startOfPeak = findStartOfPeak();

        while (startOfPeak != noPeaksFound) {
            maybeClearPeak(startOfPeak);
            startOfPeak = findStartOfPeak();
        }
    }

    Coordinate findStartOfPeak() {
        for (unsigned int x = 0; x < width; x++) {
            for (unsigned int y = 0; y < height; y++) {
                if (regionalMaximums.getPixel(x, y) > 0)
                    return Coordinate(x, y);
            }
        }

        return noPeaksFound;
    }

    void maybeClearPeak(const Coordinate& startOfPeak) {
        pixelsToUpdate.clear();
        pixelsToCheck.clear();

        pixelsToCheck.insert(pixelAt(startOfPeak));

        collectPixelsToUpdate();
        clearPixels();
    }

    void collectPixelsToUpdate() {
        while (thereAreMorePixelsToCollect()) {
            auto firstPosition = pixelsToCheck.begin();
            auto pixel = *firstPosition;

            pixelsToCheck.erase(firstPosition);

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

    void collectPixel(const Pixel& pixel) {
        pixelsToUpdate.insert(pixel);
        queueNeighbors(pixel);
    }

    void queueNeighbors(const Pixel& pixel) {
        const auto x = std::get<1>(pixel);
        const auto y = std::get<2>(pixel);

        maybeQueueNeighbor(x < maxX, x + 1, y);
        maybeQueueNeighbor(y < maxY, x, y + 1);
        maybeQueueNeighbor(x > 0, x - 1, y);
        maybeQueueNeighbor(y > 0, x, y - 1);
    }

    void maybeQueueNeighbor(bool precondition, unsigned int x, unsigned int y) {
        if (precondition)
            maybeQueuePixel(pixelAt(x, y));
    }

    void maybeQueuePixel(const Pixel& pixel) {
        if (pixelHasntBeenProcessed(pixel))
            pixelsToCheck.insert(pixel);
    }

    bool pixelHasntBeenProcessed(const Pixel& pixel) {
        auto notFound = pixelsToUpdate.end();

        return pixelsToUpdate.find(pixel) == notFound;
    }

    DestinationPixelType getValueToClearPixels() {
        auto firstPosition = pixelsToUpdate.begin();
        auto pixel = *firstPosition;
        auto value = std::get<0>(pixel);

        return value;
    }

    void updatePixel(const Pixel& pixel, const DestinationPixelType& value) {
        const auto x = std::get<1>(pixel);
        const auto y = std::get<2>(pixel);

        destinationImage.setPixel(x, y, value);
        regionalMaximums.setPixel(x, y, 0);
    }

    Pixel pixelAt(const Coordinate& coordinate) {
        const auto x = std::get<0>(coordinate);
        const auto y = std::get<1>(coordinate);

        return pixelAt(x, y);
    }

    Pixel pixelAt(unsigned int x, unsigned int y) {
        const auto height = destinationImage.getPixel(x, y);

        return Pixel(height, x, y);
    }
};

#endif
