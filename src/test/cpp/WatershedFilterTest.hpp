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

#define IMAGE_PARAMS SourcePixelType, DestinationPixelType, \
    DestinationImageType, SourceImageType

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType, typename SourceImageType>
class AbstractWatershedFilterTestData : public AbstractFilterTestData<
        WatershedFilter<IMAGE_PARAMS>, IMAGE_PARAMS> {
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
        AbstractWatershedFilterTestData<IMAGE_PARAMS>, IMAGE_PARAMS>;

#endif
