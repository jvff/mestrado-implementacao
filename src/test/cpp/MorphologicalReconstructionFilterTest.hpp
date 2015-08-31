#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractImageTransformationTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "MorphologicalReconstructionTestData.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractMorphologicalReconstructionFilterTestData
        : public AbstractImageTransformationTestData<PixelType, PixelType,
                ImageType, ImageType> {
private:
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using ImagePointer = std::unique_ptr<ImageType>;
    using SuperClass = AbstractImageTransformationTestData<PixelType, PixelType,
            ImageType, ImageType>;

protected:
    using State = typename SuperClass::State;

public:
    FilterType filter;
    ImagePointer markerImage;

public:
    bool setDimensions(unsigned int newWidth, unsigned int newHeight) {
        if (SuperClass::setDimensions(newWidth, newHeight)) {
            markerImage.reset(new ImageType(newWidth, newHeight));

            this->state = State::SETTING_UP;

            return true;
        } else
            return false;
    }

private:
    ImageType transformImage() override {
        filter.apply(*this->sourceImage, *markerImage);

        return *markerImage;
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalReconstructionTestData<
        AbstractMorphologicalReconstructionFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
