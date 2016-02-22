#ifndef PIXEL_NEIGHBORHOOD_HPP
#define PIXEL_NEIGHBORHOOD_HPP

#include <functional>

#include "Image.hpp"

template <typename PixelType>
class PixelNeighborhood {
private:
    using PixelComparator = std::function<bool(const Pixel<PixelType>&,
            const Pixel<PixelType>&)>;

public:
    bool hasAvailableNeighbor(const Image<bool>& maskImage, unsigned int x,
            unsigned int y) {
        auto maxX = maskImage.getWidth() - 1;
        auto maxY = maskImage.getHeight() - 1;

        return isNeighborAvailable(maskImage, x - 1, y, x > 0)
            || isNeighborAvailable(maskImage, x, y - 1, y > 0)
            || isNeighborAvailable(maskImage, x + 1, y, x < maxX)
            || isNeighborAvailable(maskImage, x, y + 1, y < maxY);
    }

    Pixel<PixelType> getBestNeighbor(const Image<PixelType>& image,
            const Image<bool>& maskImage, unsigned int x, unsigned int y,
            PixelComparator comparator) {
        auto maxX = image.getWidth() - 1;
        auto maxY = image.getHeight() - 1;

        return selectBestNeighborCandidate(image, maskImage, comparator,
                x > 0, x - 1, y,
                y > 0, x, y - 1,
                x < maxX, x + 1, y,
                y < maxY, x, y + 1);
    }

private:
    bool isNeighborAvailable(const Image<bool>& maskImage, unsigned int x,
            unsigned int y, bool neighborCoordinateIsValid) {
        if (neighborCoordinateIsValid == false)
            return false;

        auto neighborHasBeenProcessed = maskImage.getPixelValue(x, y);

        return neighborHasBeenProcessed == false;
    }

    template <typename... RemainingParameterTypes>
    Pixel<PixelType> selectBestNeighborCandidate(const Image<PixelType>& image,
            const Image<bool>& maskImage, PixelComparator comparator,
            bool coordinateIsValid, unsigned int x, unsigned int y,
            RemainingParameterTypes... remainingParameters) {
        if (coordinateIsValid) {
            auto neighborHasBeenProcessed = maskImage.getPixelValue(x, y);

            if (!neighborHasBeenProcessed) {
                auto bestNeighbor = image.getPixel(x, y);

                return selectBestNeighborCandidate(bestNeighbor, image,
                        maskImage, comparator, remainingParameters...);
            }
        }

        return selectBestNeighborCandidate(image, maskImage, comparator,
                remainingParameters...);
    }

    Pixel<PixelType> selectBestNeighborCandidate(const Image<PixelType>&,
            const Image<bool>&, PixelComparator) {
        throw "No candidate available";
    }

    template <typename... RemainingParameterTypes>
    Pixel<PixelType> selectBestNeighborCandidate(Pixel<PixelType> bestNeighbor,
            const Image<PixelType>& image, const Image<bool>& maskImage,
            PixelComparator comparator, bool coordinateIsValid, unsigned int x,
            unsigned int y, RemainingParameterTypes... remainingParameters) {
        if (coordinateIsValid) {
            auto neighborHasBeenProcessed = maskImage.getPixelValue(x, y);

            if (!neighborHasBeenProcessed) {
                auto candidate = image.getPixel(x, y);

                if (comparator(bestNeighbor, candidate))
                    bestNeighbor = candidate;
            }
        }

        return selectBestNeighborCandidate(bestNeighbor, image, maskImage,
                comparator, remainingParameters...);
    }

    Pixel<PixelType> selectBestNeighborCandidate(Pixel<PixelType> bestNeighbor,
            const Image<PixelType>&, const Image<bool>&, PixelComparator) {
        return bestNeighbor;
    }
};

#endif
