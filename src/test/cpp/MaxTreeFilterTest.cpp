#include <functional>

#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "MinMaxTreeTestData.hpp"
#include "MinMaxTreeTests.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractMaxTreeFilterTestData : public AbstractFilterTestData<
        MaxTreeFilter<ImageType, ImageType>, ImageType,
        MaxTreeImage<ImageType> > {
public:
    AbstractMaxTreeFilterTestData() {
        this->initializeFilter();
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MinMaxTreeTestData<AbstractMaxTreeFilterTestData<PixelType,
            ImageType>, std::less, PixelType, ImageType>;

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MaxTreeFilterTest, MinMaxTreeTests,
        TestData);
