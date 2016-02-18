#include <functional>

#include "MinTreeImage.hpp"
#include "MinTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "MinMaxTreeTests.hpp"
#include "MinMaxTreeTestData.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MinMaxTreeTestData<AbstractFilterImplementationTestData<
            MinTreeImplementation<ImageType, ImageType>,
            ImageType, MinTreeImage<ImageType> >,
        std::greater, PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MinTreeImplementationTest, MinMaxTreeTests,
        TestData);
