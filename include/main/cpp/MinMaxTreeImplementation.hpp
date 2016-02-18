#ifndef MIN_MAX_TREE_IMPLEMENTATION_HPP
#define MIN_MAX_TREE_IMPLEMENTATION_HPP

#include <functional>
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
        MinMaxTreeImage<InternalImageType,
                TreeTypeComparator<typename InternalImageType::PixelType> > > {
private:
    using DestinationPixelType = typename InternalImageType::PixelType;
    using LevelOrderComparator = TreeTypeComparator<DestinationPixelType>;
    using DestinationImageType = MinMaxTreeImage<InternalImageType,
            LevelOrderComparator>;
    using PixelType = typename SourceImageType::PixelType;
    using PixelValueComparator = TreeTypeComparator<PixelType>;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using PixelComparator = TreeTypeComparator<Pixel<PixelType> >;
    using PixelQueue = std::priority_queue<Pixel<PixelType>,
            std::vector<Pixel<PixelType> >, PixelComparator>;

    enum class Direction { LEFT, RIGHT, UP, DOWN };

    PixelValueComparator isCloserToRootLevel;
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
        auto startingPixel = findRootPixel();

        setFirstDestinationPixel(startingPixel);

        pixelQueue.push(startingPixel);
        queuedOrFinishedPixels.setPixel(startingPixel.x, startingPixel.y, true);
    }

    Pixel<PixelType> findRootPixel() {
        auto rootPixel = sourceImage.getPixel(0, 0);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y) {
                auto currentPixel = sourceImage.getPixel(x, y);

                if (isCloserToRootLevel(currentPixel.value, rootPixel.value))
                    rootPixel = currentPixel;
            }
        }

        return rootPixel;
    }

    void processQueue() {
        while (!pixelQueue.empty())
            processPixel(pixelQueue.top());
    }

    void processPixel(Pixel<PixelType> pixel) {
        if (allNeighborsHaveBeenProcessed(pixel))
            finishPixel();
        else
            queueNeighborOnFarthestLevel(pixel);
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

    void queueNeighborOnFarthestLevel(Pixel<PixelType> pixel) {
        auto neighbor = getNeighborOnFarthestLevel(pixel);

        processPixelNeighbor(pixel, neighbor);
    }

    Pixel<PixelType> getNeighborOnFarthestLevel(Pixel<PixelType> pixel) {
        auto neighbor = pixel;
        bool hasBeenSet = false;

        getNeighborIfFarther(pixel, Direction::LEFT, neighbor, hasBeenSet);
        getNeighborIfFarther(pixel, Direction::RIGHT, neighbor, hasBeenSet);
        getNeighborIfFarther(pixel, Direction::UP, neighbor, hasBeenSet);
        getNeighborIfFarther(pixel, Direction::DOWN, neighbor, hasBeenSet);

        return neighbor;
    }

    void getNeighborIfFarther(const Pixel<PixelType> &pixel,
            Direction direction, Pixel<PixelType> &bestNeighbor,
            bool& bestNeighborHasBeenSet) {
        if (neighborIsValid(pixel, direction)
                && !neighborHasBeenProcessed(pixel, direction)) {
            auto neighborCoordinate = getPixelNeighbor(pixel, direction);
            auto neighbor = sourceImage.getPixel(neighborCoordinate);

            if (!bestNeighborHasBeenSet) {
                bestNeighbor = neighbor;
                bestNeighborHasBeenSet = true;
            } else if (isCloserToRootLevel(bestNeighbor.value, neighbor.value))
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

        if (isCloserToRootLevel(pixel.value, neighbor.value))
            destinationImage.assignPixelToNewNode(x, y);
        else {
            destinationImage.assignPixelToLatestNode(x, y);

            if (isCloserToRootLevel(neighbor.value, pixel.value))
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
