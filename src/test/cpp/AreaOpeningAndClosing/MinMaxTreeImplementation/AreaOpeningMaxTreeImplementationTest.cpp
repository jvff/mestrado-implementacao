#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "../../AbstractFilterImplementationTestData.hpp"

#include "../AreaOpeningAndClosingTestData.hpp"
#include "../AreaOpeningTests.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaOpeningMaxTreeImplementationTestData
        : public AbstractFilterImplementationTestData<
                AreaOpeningMaxTreeImplementation<ImageType, ImageType>,
                ImageType, ImageType> {
private:
    using ImplementationType = AreaOpeningMaxTreeImplementation<ImageType,
            ImageType>;

protected:
    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        return ImplementationType(getMaximumExtremitySize(), sourceImage,
                destinationImage);
    }

    virtual unsigned int getMaximumExtremitySize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningAndClosingTestData<
        AbstractAreaOpeningMaxTreeImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(AreaOpeningMaxTreeImplementationTest,
        AreaOpeningTests, TestData);
