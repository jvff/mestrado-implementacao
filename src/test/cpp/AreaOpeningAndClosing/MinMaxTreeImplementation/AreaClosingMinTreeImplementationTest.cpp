#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingMinTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "../../AbstractFilterImplementationTestData.hpp"

#include "../AreaClosingTests.hpp"
#include "../AreaOpeningAndClosingTestData.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaClosingMinTreeImplementationTestData
        : public AbstractFilterImplementationTestData<
                AreaClosingMinTreeImplementation<ImageType, ImageType>,
                ImageType, ImageType> {
private:
    using ImplementationType = AreaClosingMinTreeImplementation<ImageType,
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
        AbstractAreaClosingMinTreeImplementationTestData<PixelType, ImageType>,
        PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(AreaClosingMinTreeImplementationTest,
        AreaClosingTests, TestData);
