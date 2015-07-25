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
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        for (unsigned int x = 0; x < maxX; ++x) {
            for (unsigned int y = 0; y < maxY; ++y) {
                const PixelType& markerPixel = destinationImage.getPixel(x, y);
                const PixelType& sourcePixel = sourceImage.getPixel(x, y);
                const PixelType& rightPixel = sourceImage.getPixel(x + 1, y);
                const PixelType& oldPixel = destinationImage.getPixel(x + 1, y);

                PixelType currentPixel = std::min(markerPixel, sourcePixel);
                PixelType newRightPixel = std::min(currentPixel, rightPixel);
                PixelType destinationPixel = std::max(newRightPixel, oldPixel);

                destinationImage.setPixel(x + 1, y, destinationPixel);
            }
        }
    }

protected:
    PixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }
};

#endif
