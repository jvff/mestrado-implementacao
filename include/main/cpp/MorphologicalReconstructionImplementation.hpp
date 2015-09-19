#ifndef MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP

#include <queue>

#include "Coordinate.hpp"
#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class MorphologicalReconstructionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using PixelType = typename DestinationImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    enum class Direction { LEFT, RIGHT, UP, DOWN };

private:
    std::queue<Coordinate> pixelsToBeUpdated;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::maxX;
    using SuperClass::maxY;

public:
    MorphologicalReconstructionImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
        avoidMarkersBiggerThanSourcePixels();
        firstPass();
        secondPass();
        thirdPass();
    }

private:
    void avoidMarkersBiggerThanSourcePixels() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                const auto sourcePixel = sourceImage.getPixelValue(x, y);
                const auto markerPixel = destinationImage.getPixelValue(x, y);
                const auto truncatedMarkerPixel =
                        std::min(markerPixel, sourcePixel);

                destinationImage.setPixel(x, y, truncatedMarkerPixel);
            }
        }
    }

    void firstPass() {
        auto pixel = Coordinate(0, 0);

        for (pixel.x = 0; pixel.x < maxX; ++pixel.x) {
            for (pixel.y = 0; pixel.y < maxY; ++pixel.y) {
                propagate(pixel, Direction::RIGHT);
                propagate(pixel, Direction::DOWN);
            }
        }

        propagate(Coordinate(maxX - 1, maxY), Direction::RIGHT);
        propagate(Coordinate(maxX, maxY - 1), Direction::DOWN);
    }

    void secondPass() {
        Coordinate pixel;

        for (pixel.x = maxX; pixel.x > 0; --pixel.x) {
            for (pixel.y = maxY; pixel.y > 0; --pixel.y) {
                tryToPropagateAndQueue(pixel, Direction::LEFT);
                tryToPropagateAndQueue(pixel, Direction::UP);
            }
        }
    }

    void thirdPass() {
        while (!pixelsToBeUpdated.empty()) {
            auto pixel = pixelsToBeUpdated.front();

            tryToPropagateAndQueue(pixel, Direction::LEFT);
            tryToPropagateAndQueue(pixel, Direction::RIGHT);
            tryToPropagateAndQueue(pixel, Direction::UP);
            tryToPropagateAndQueue(pixel, Direction::DOWN);

            pixelsToBeUpdated.pop();
        }
    }

    void propagate(const Coordinate& pixel, Direction direction) {
        propagatePixel(pixel, getNeighbor(pixel, direction));
    }

    void tryToPropagateAndQueue(const Coordinate& pixel, Direction direction) {
        auto neighbor = getNeighbor(pixel, direction);

        if (propagatePixel(pixel, neighbor))
            pixelsToBeUpdated.push(neighbor);
    }

    Coordinate getNeighbor(const Coordinate& pixel, Direction direction) {
        auto neighbor = pixel;

        switch (direction) {
            case Direction::LEFT:
                neighbor.x -= 1;
                break;
            case Direction::RIGHT:
                neighbor.x += 1;
                break;
            case Direction::UP:
                neighbor.y -= 1;
                break;
            case Direction::DOWN:
                neighbor.y += 1;
                break;
        };

        return neighbor;
    }

    bool propagatePixel(const Coordinate& source, const Coordinate& target) {
        if (coordinateIsInvalid(target))
            return false;

        const auto markerCurrent = destinationImage.getPixelValue(source);
        const auto markerNext = destinationImage.getPixelValue(target);
        const auto sourceValue = sourceImage.getPixelValue(target);

        const auto propagatedValue = std::min(markerCurrent, sourceValue);
        const auto destinationValue = std::max(propagatedValue, markerNext);

        destinationImage.setPixel(target, destinationValue);

        return markerNext != destinationValue;
    }

    bool coordinateIsInvalid(const Coordinate& coordinate) {
        return coordinate.x > maxX || coordinate.y > maxY;
    }
};

#endif
