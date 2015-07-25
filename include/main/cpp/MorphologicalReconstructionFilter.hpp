#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP

#include "Filter.hpp"

template <typename PixelType, class DestinationImageType,
        class SourceImageType = Image<PixelType> >
class MorphologicalReconstructionFilter
        : public Filter<PixelType, PixelType, DestinationImageType,
                SourceImageType> {
private:
    using ParentFilter = Filter<PixelType, PixelType, DestinationImageType,
            SourceImageType>;

public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        avoidMarkersBiggerThanSourcePixels(sourceImage, destinationImage);
        firstPass(sourceImage, destinationImage);
    }

protected:
    PixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }

private:
    void avoidMarkersBiggerThanSourcePixels(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                const PixelType sourcePixel = sourceImage.getPixel(x, y);
                const PixelType markerPixel = destinationImage.getPixel(x, y);
                const PixelType truncatedMarkerPixel =
                        std::min(markerPixel, sourcePixel);

                destinationImage.setPixel(x, y, truncatedMarkerPixel);
            }
        }
    }

    void firstPass(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        for (unsigned int x = 0; x < maxX; ++x) {
            for (unsigned int y = 0; y < maxY; ++y) {
                propagateRight(sourceImage, destinationImage, x, y);
                propagateDown(sourceImage, destinationImage, x, y);
            }
        }
    }

    void propagateRight(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        const PixelType markerCenter = destinationImage.getPixel(x, y);
        const PixelType markerRight = destinationImage.getPixel(x + 1, y);
        const PixelType sourceRight = sourceImage.getPixel(x + 1, y);

        const PixelType newRightPixel = std::min(markerCenter, sourceRight);
        const PixelType destinationPixel = std::max(newRightPixel, markerRight);

        destinationImage.setPixel(x + 1, y, destinationPixel);
    }

    void propagateDown(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, unsigned int x,
            unsigned int y) {
        const PixelType markerCenter = destinationImage.getPixel(x, y);
        const PixelType markerDown = destinationImage.getPixel(x, y + 1);
        const PixelType sourceDown = sourceImage.getPixel(x, y + 1);

        const PixelType newDownPixel = std::min(markerCenter, sourceDown);
        const PixelType destinationPixel = std::max(newDownPixel, markerDown);

        destinationImage.setPixel(x, y + 1, destinationPixel);
    }
};

#endif
