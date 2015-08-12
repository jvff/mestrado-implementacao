#ifndef ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include <cmath>

#include "Filter.hpp"
#include "MorphologicalGradientFilter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AdjustedMorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
private:
    using MorphologicalGradientFilterType = MorphologicalGradientFilter<
            SourcePixelType, DestinationPixelType, DestinationImageType,
            SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    MorphologicalGradientFilterType unadjustedFilter;
    SourcePixelType activationThreshold;
    float normalizationFactor;
    float normalizationDivisor;
    float adjustmentExponent;

public:
    AdjustedMorphologicalGradientFilter(unsigned int structureSize,
            const SourcePixelType& activationThreshold,
            const DestinationPixelType& maxPixelValue,
            float adjustmentExponent) : unadjustedFilter(structureSize) {
        this->activationThreshold = activationThreshold;
        this->adjustmentExponent = adjustmentExponent;

        normalizationDivisor = (float)maxPixelValue;
        normalizationFactor = 1.f / normalizationDivisor;
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        unadjustedFilter.apply(sourceImage, destinationImage);
        applyAdjustment(sourceImage, destinationImage);
    }

    using SuperClass::apply;

private:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }

    void applyAdjustment(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                maybeAdjustPixel(x, y, sourceImage, destinationImage);
        }
    }

    void maybeAdjustPixel(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        auto sourcePixel = sourceImage.getPixel(x, y);

        if (sourcePixel < activationThreshold)
            adjustPixel(x, y, destinationImage);
    }

    void adjustPixel(unsigned int x, unsigned int y,
            DestinationImageType& destinationImage) {
        float unadjustedValue = (float)destinationImage.getPixel(x, y);
        float normalizedUnadjustedValue = unadjustedValue * normalizationFactor;
        float normalizedAdjustedValue = std::pow(normalizedUnadjustedValue,
                adjustmentExponent);
        float adjustedValue = normalizedAdjustedValue * normalizationDivisor;

        destinationImage.setPixel(x, y, (DestinationPixelType)adjustedValue);
    }
};

#endif
