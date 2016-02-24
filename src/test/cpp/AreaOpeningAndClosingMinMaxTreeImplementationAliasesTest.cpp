#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaOpeningAndClosingMinMaxTreeImplementationAliasesTest,
        aliasForAreaOpeningMaxTreeImplementationExists) {
    using SourcePixelType = DummyTypes<0>;
    using DestinationPixelType = DummyTypes<1>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;

    using AreaOpeningMaxTreeImplementationAlias =
            AreaOpeningMaxTreeImplementation<SourceImageType,
                    DestinationImageType>;
    using ExpectedType = AreaOpeningAndClosingMinMaxTreeImplementation<
            SourceImageType, DestinationImageType, std::less>;

    AssertThat<AreaOpeningMaxTreeImplementationAlias>
            ::isTheSame(As<ExpectedType>());
}
