#ifndef MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include <algorithm>

#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"
#include "SimpleFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class MorphologicalGradientFilter : public SimpleFilter<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using ParentFilter = SimpleFilter<SourceImageType, DestinationImageType>;
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
        auto pixel = sourceImage.getPixelValue(x, y);
        auto maxX = sourceImage.getWidth() - 1;
        auto maxY = sourceImage.getHeight() - 1;

        auto startU = (unsigned int)std::max(0, (int)(x - structureSize));
        auto startV = (unsigned int)std::max(0, (int)(y - structureSize));
        auto endU = std::min(maxX, x + structureSize);
        auto endV = std::min(maxY, y + structureSize);

        for (unsigned int u = startU; u <= endU; ++u) {
            for (unsigned int v = startV; v <= endV; ++v)
                pixel = operation(pixel, sourceImage.getPixelValue(u, v));
        }

        return pixel;
    }
};

template <typename PixelType>
class MorphologicalGradientFilter<OpenCLImage<PixelType>,
        OpenCLImage<PixelType> >
        : public OpenCLFilter<PixelType, unsigned int> {
};

#endif
