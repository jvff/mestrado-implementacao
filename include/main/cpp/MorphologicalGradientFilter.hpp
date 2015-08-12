#ifndef MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include <algorithm>

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class MorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
private:
    using ParentFilter = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using OperationType = const DestinationPixelType& (*)(
            const DestinationPixelType&, const DestinationPixelType&);

    unsigned int structureSize;

public:
    MorphologicalGradientFilter(unsigned int structureSize) {
        this->structureSize = structureSize;
    }

    using ParentFilter::apply;

protected:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return dilate(x, y, sourceImage) - erode(x, y, sourceImage);
    }

    DestinationPixelType dilate(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        OperationType maxOperation = std::max<DestinationPixelType>;

        return selectPixelInStructure(x, y, sourceImage, maxOperation);
    }

    DestinationPixelType erode(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        OperationType minOperation = std::min<DestinationPixelType>;

        return selectPixelInStructure(x, y, sourceImage, minOperation);
    }

    DestinationPixelType selectPixelInStructure(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage, OperationType operation) {
        auto pixel = sourceImage.getPixel(x, y);
        auto maxX = sourceImage.getWidth() - 1;
        auto maxY = sourceImage.getHeight() - 1;

        auto startU = (unsigned int)std::max(0, (int)(x - structureSize));
        auto startV = (unsigned int)std::max(0, (int)(y - structureSize));
        auto endU = std::min(maxX, x + structureSize);
        auto endV = std::min(maxY, y + structureSize);

        for (unsigned int u = startU; u <= endU; ++u) {
            for (unsigned int v = startV; v <= endV; ++v)
                pixel = operation(pixel, sourceImage.getPixel(u, v));
        }

        return pixel;
    }
};

#endif