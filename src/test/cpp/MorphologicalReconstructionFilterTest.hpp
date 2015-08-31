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

class MorphologicalReconstructionFilterTest : public testing::Test {
protected:
    using PixelType = DummyType;
    using SourceImageType = Image<PixelType>;
    using DestinationImageType = FakeImage<PixelType>;
    using ImplementationType = MorphologicalReconstructionImplementation<
            SourceImageType, DestinationImageType>;
    using DummyFilterType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;
};

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
    ImagePointer destinationImage;

private:
    ImageType transformImage() override {
        filter.apply(*this->sourceImage, *destinationImage);

        return *destinationImage;
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalReconstructionTestData<
        AbstractMorphologicalReconstructionFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
