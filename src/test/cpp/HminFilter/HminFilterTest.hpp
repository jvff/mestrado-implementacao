#ifndef HMIN_FILTER_TEST_HPP
#define HMIN_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "HminFilter.hpp"
#include "HminImplementation.hpp"

#include "../AbstractFilterTestData.hpp"
#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#include "HminTestData.hpp"

class HminFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HminFilter<SourceImageType, DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class HminFilterTestData : public AbstractFilterTestData<
        HminFilter<ImageType, ImageType>, ImageType, ImageType> {
protected:
    void runTest() override {
        this->initializeFilter(getFeatureHeight());
    }

    virtual PixelType getFeatureHeight() = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = HminTestData<HminFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
