#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MinMaxTreeImplementationAliasesTest, aliasForMaxTreeImplementationExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;

    using MaxTreeImplementationAlias = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, std::less>;

    AssertThat<MaxTreeImplementationAlias>::isTheSame(As<ExpectedType>());
}
