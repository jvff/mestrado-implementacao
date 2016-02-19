#include <functional>

#include "MinTreeFilter.hpp"
#include "MinTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "MinMaxTreeTestData.hpp"
#include "MinMaxTreeTests.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractMinTreeFilterTestData : public AbstractFilterTestData<
        MinTreeFilter<ImageType, ImageType>, ImageType,
        MinTreeImage<ImageType> > {
public:
    AbstractMinTreeFilterTestData() {
        this->initializeFilter();
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MinMaxTreeTestData<AbstractMinTreeFilterTestData<PixelType,
            ImageType>, std::greater, PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MinTreeFilterTest, MinMaxTreeTests,
        TestData);
