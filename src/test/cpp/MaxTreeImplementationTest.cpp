#include <functional>

#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "MaxTreeTestData.hpp"
#include "MaxTreeTests.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MaxTreeTestData<AbstractFilterImplementationTestData<
            MaxTreeImplementation<ImageType, ImageType>,
            ImageType, MaxTreeImage<ImageType> >,
        std::less, PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MaxTreeImplementationTest,
        MaxTreeTests, TestData);
