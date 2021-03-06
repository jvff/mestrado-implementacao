#ifndef WATERSHED_FILTER_TEST_HPP
#define WATERSHED_FILTER_TEST_HPP

#include <initializer_list>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "WatershedFilter.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "WatershedTestData.hpp"

class WatershedFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = WatershedFilter<SourceImageType, DestinationImageType>;
};

template <typename SourceImageType, typename DestinationImageType>
class AbstractWatershedFilterTestData : public AbstractFilterTestData<
        WatershedFilter<SourceImageType, DestinationImageType>,
        SourceImageType, DestinationImageType> {
public:
    AbstractWatershedFilterTestData() {
        this->initializeFilter();
    }
};

template <typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
using TestData = WatershedTestData<
        AbstractWatershedFilterTestData<SourceImageType, DestinationImageType>,
        SourceImageType, DestinationImageType>;

#endif
