#ifndef WATERSHED_IMPLEMENTATION_TEST_HPP
#define WATERSHED_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"
#include "WatershedImplementation.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "WatershedTestData.hpp"

#define IMAGE_PARAMS SourcePixelType, DestinationPixelType, \
    DestinationImageType, SourceImageType

template <typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
using TestData = WatershedTestData<
        AbstractFilterImplementationTestData<
            WatershedImplementation<IMAGE_PARAMS>, IMAGE_PARAMS>,
        IMAGE_PARAMS>;

#endif
