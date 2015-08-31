#ifndef MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionImplementation.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "MorphologicalReconstructionTestData.hpp"

class MorphologicalReconstructionImplementationTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = MorphologicalReconstructionImplementation<
            SourceImageType, DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalReconstructionTestData<
        AbstractFilterImplementationTestData<
                MorphologicalReconstructionImplementation<ImageType, ImageType>,
                PixelType, PixelType, ImageType, ImageType>,
        PixelType, ImageType>;

#endif
