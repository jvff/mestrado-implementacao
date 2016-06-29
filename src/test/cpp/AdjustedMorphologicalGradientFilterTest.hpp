#ifndef ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_TEST_HPP
#define ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AdjustedMorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "MorphologicalGradientFilter/AbstractMorphologicalGradientTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType = unsigned char,
        typename ImageType = SimpleArrayImage<PixelType> >
class AdjustedMorphologicalGradientFilterTestData
        : public AbstractMorphologicalGradientTestData<
                AdjustedMorphologicalGradientFilter<Image<PixelType>,
                        ImageType>,
                PixelType, ImageType> {
private:
    using FilterType = AdjustedMorphologicalGradientFilter<Image<PixelType>,
            ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractMorphologicalGradientTestData<FilterType,
            PixelType, ImageType>;
    using ThisType = AdjustedMorphologicalGradientFilterTestData<PixelType,
            ImageType>;

    bool structureSizeIsSet = false;
    bool activationThresholdIsSet = false;
    bool maxPixelValueIsSet = false;
    bool adjustmentExponentIsSet = false;

    PixelType activationThreshold = 1;
    PixelType maxPixelValue = 0xFF;
    float adjustmentExponent = 0.01;

public:
    ~AdjustedMorphologicalGradientFilterTestData() {
        maybeAdjustImage();
        this->tryToRunTest();
    }

    CHAIN(setStructureSize, unsigned int size) {
        if (SuperClass::setStructureSize(size)) {
            structureSizeIsSet = true;
            maybeInitializeFilter();
        }
    }

    CHAIN(setActivationThreshold, const PixelType& threshold) {
        setParameter(activationThreshold, threshold, activationThresholdIsSet);
    }

    CHAIN(setMaxPixelValue, const PixelType& maxValue) {
        setParameter(maxPixelValue, maxValue, maxPixelValueIsSet);
    }

    CHAIN(setAdjustmentExponent, float exponent) {
        setParameter(adjustmentExponent, exponent, adjustmentExponentIsSet);
    }

    CHAIN_PARENT_METHOD(setDimensions)
    CHAIN_PARENT_METHOD(setBackground)
    CHAIN_PARENT_METHOD(drawSquare)

private:
    using SuperClass::stateIs;

    void maybeAdjustImage() {
        if (stateIs(State::READY))
            adjustImage();
    }

    void adjustImage() {
        *this->expectedImage = [this] (unsigned int x, unsigned int y)
                -> PixelType {
            auto pixel = this->expectedImage->getPixelValue(x, y);

            if (shouldAdjustPixel(x, y))
                adjustPixel(pixel);

            return pixel;
        };
    }

    bool shouldAdjustPixel(unsigned int x, unsigned int y) {
        return this->sourceImage->getPixelValue(x, y) < activationThreshold;
    }

    void adjustPixel(PixelType& pixel) {
        auto value = (float)pixel;
        auto maxValue = (float)maxPixelValue;
        auto normalized = value / maxValue;
        auto adjustedNormalized = std::pow(normalized, adjustmentExponent);
        auto adjustedValue = adjustedNormalized * maxValue;

        pixel = (PixelType)adjustedValue;
    }

    template <typename ParameterType>
    void setParameter(ParameterType& parameter, const ParameterType& value,
            bool& parameterIsSet) {
        if (parameterIsSet)
            this->cancelTestExecution();
        else {
            parameter = value;
            parameterIsSet = true;

            maybeInitializeFilter();
        }
    }

    void maybeInitializeFilter() {
        if (filterParametersHaveBeenSet()) {
            this->initializeFilter(this->structureSize, activationThreshold,
                    maxPixelValue, adjustmentExponent);
        }
    }

    bool filterParametersHaveBeenSet() {
        return structureSizeIsSet && activationThresholdIsSet
            && maxPixelValueIsSet && adjustmentExponentIsSet;
    }
};

#endif
