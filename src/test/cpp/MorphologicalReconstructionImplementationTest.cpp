#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MorphologicalReconstructionImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = MorphologicalReconstructionImplementation<
            SourceImageType, DestinationImageType>;

    AssertThat<DummyImplementationType>::isClassOrStruct();
}
