#ifndef MAX_TREE_FILTER_TEST_HPP
#define MAX_TREE_FILTER_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

#include "AbstractFilterTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "MaxTreeTestData.hpp"

class MaxTreeFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DummyMaxTreeFilter = MaxTreeFilter<SourceImageType,
            InternalImageType>;
};

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
using TestData = MaxTreeTestData<AbstractMaxTreeFilterTestData<PixelType,
            ImageType>, std::less, PixelType, ImageType>;

#endif
