#ifndef MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MorphologicalReconstructionImplementationTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = MorphologicalReconstructionImplementation<
            SourceImageType, DestinationImageType>;
};

#endif
