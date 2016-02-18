#ifndef MIN_MAX_TREE_IMPLEMENTATION_HPP
#define MIN_MAX_TREE_IMPLEMENTATION_HPP

#include <queue>
#include <vector>

#include "Coordinate.hpp"
#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"
#include "Pixel.hpp"
#include "SimpleArrayImage.hpp"

template <typename SourceImageType, typename InternalImageType,
         template <typename> class TreeTypeComparator>
class MinMaxTreeImplementation : public FilterImplementation<SourceImageType,
        MaxTreeImage<InternalImageType> > {
private:
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using PixelType = typename SourceImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using AscendingPixelComparator =
            typename Pixel<PixelType>::AscendingComparator;
    using PixelQueue = std::priority_queue<Pixel<PixelType>,
            std::vector<Pixel<PixelType> >, AscendingPixelComparator>;

    enum class Direction { LEFT, RIGHT, UP, DOWN };

    PixelQueue pixelQueue;
    SimpleArrayImage<bool> queuedOrFinishedPixels;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::maxX;
    using SuperClass::maxY;

public:
    MinMaxTreeImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            queuedOrFinishedPixels(width, height) {
    }

    void apply() override {
        initializeQueuedOrFinishedPixelImage();
        queueStartingPixel();
        processQueue();
    }

private:
    void initializeQueuedOrFinishedPixelImage() {
        queuedOrFinishedPixels = [] (unsigned int, unsigned int) -> bool {
            return false;
        };
    }

    void queueStartingPixel() {
        auto startingPixel = findLowestPixel();

        setFirstDestinationPixel(startingPixel);

        pixelQueue.push(startingPixel);
        queuedOrFinishedPixels.setPixel(startingPixel.x, startingPixel.y, true);
    }

    Pixel<PixelType> findLowestPixel() {
        auto lowestPixel = sourceImage.getPixel(0, 0);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                auto currentPixel = sourceImage.getPixel(x, y);

                if (currentPixel.value < lowestPixel.value)
                    lowestPixel = currentPixel;
            }
        }

        return lowestPixel;
    }

    void processQueue() {
        while (!pixelQueue.empty())
            processPixel(pixelQueue.top());
    }

    void processPixel(Pixel<PixelType> pixel) {
        if (allNeighborsHaveBeenProcessed(pixel))
            finishPixel();
        else
            queueHighestNeighbor(pixel);
    }

    bool allNeighborsHaveBeenProcessed(Pixel<PixelType> pixel) {
        return neighborHasBeenProcessed(pixel, Direction::LEFT)
            && neighborHasBeenProcessed(pixel, Direction::UP)
            && neighborHasBeenProcessed(pixel, Direction::RIGHT)
            && neighborHasBeenProcessed(pixel, Direction::DOWN);
    }

    bool neighborHasBeenProcessed(Pixel<PixelType> pixel, Direction direction) {
        if (!neighborIsValid(pixel, direction))
            return true;

        auto neighbor = getPixelNeighbor(pixel, direction);

        return queuedOrFinishedPixels.getPixelValue(neighbor);
    }

    bool neighborIsValid(Pixel<PixelType> pixel, Direction direction) {
        switch (direction) {
            case Direction::LEFT:   return pixel.x > 0;
            case Direction::RIGHT:  return pixel.x < maxX;
            case Direction::UP:     return pixel.y > 0;
            case Direction::DOWN:   return pixel.y < maxY;
            default:                return false;
        };
    }

    Coordinate getPixelNeighbor(Pixel<PixelType> pixel, Direction direction) {
        switch (direction) {
            case Direction::LEFT:   return Coordinate(pixel.x - 1, pixel.y);
            case Direction::RIGHT:  return Coordinate(pixel.x + 1, pixel.y);
            case Direction::UP:     return Coordinate(pixel.x, pixel.y - 1);
            case Direction::DOWN:   return Coordinate(pixel.x, pixel.y + 1);
            default:                return Coordinate(pixel.x, pixel.y);
        };
    }

    void queueHighestNeighbor(Pixel<PixelType> pixel) {
        auto neighbor = getHighestNeighbor(pixel);

        processPixelNeighbor(pixel, neighbor);
    }

    Pixel<PixelType> getHighestNeighbor(Pixel<PixelType> pixel) {
        auto neighbor = pixel;
        bool hasBeenSet = false;

        getNeighborIfHigher(pixel, Direction::LEFT, neighbor, hasBeenSet);
        getNeighborIfHigher(pixel, Direction::RIGHT, neighbor, hasBeenSet);
        getNeighborIfHigher(pixel, Direction::UP, neighbor, hasBeenSet);
        getNeighborIfHigher(pixel, Direction::DOWN, neighbor, hasBeenSet);

        return neighbor;
    }

    void getNeighborIfHigher(const Pixel<PixelType> &pixel, Direction direction,
            Pixel<PixelType> &bestNeighbor, bool& bestNeighborHasBeenSet) {
        if (neighborIsValid(pixel, direction)
                && !neighborHasBeenProcessed(pixel, direction)) {
            auto neighborCoordinate = getPixelNeighbor(pixel, direction);
            auto neighbor = sourceImage.getPixel(neighborCoordinate);

            if (!bestNeighborHasBeenSet) {
                bestNeighbor = neighbor;
                bestNeighborHasBeenSet = true;
            } else if (neighbor.value > bestNeighbor.value)
                bestNeighbor = neighbor;
        }
    }

    void processPixelNeighbor(Pixel<PixelType> pixel,
            Pixel<PixelType> neighbor) {
        setDestinationPixel(pixel, neighbor);

        pixelQueue.push(neighbor);
        queuedOrFinishedPixels.setPixel(neighbor.x, neighbor.y, true);
    }

    void setDestinationPixel(Pixel<PixelType> pixel,
            Pixel<PixelType> neighbor) {
        auto x = neighbor.x;
        auto y = neighbor.y;

        destinationImage.setPixel(neighbor);

        if (pixel.value < neighbor.value)
            destinationImage.assignPixelToNewNode(x, y);
        else {
            destinationImage.assignPixelToLatestNode(x, y);

            if (pixel.value > neighbor.value)
                destinationImage.connectPixels(pixel.x, pixel.y, x, y);
        }
    }

    void setFirstDestinationPixel(Pixel<PixelType> pixel) {
        destinationImage.setPixel(pixel);
        destinationImage.assignPixelToNewNode(pixel.x, pixel.y);
    }

    void finishPixel() {
        pixelQueue.pop();
    }
};

#endif
