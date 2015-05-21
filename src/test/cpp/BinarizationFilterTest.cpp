#include <gtest/gtest.h>

#include "Filter.hpp"
#include "BinarizationFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(BinarizationFilterTest, classIsntAbstract) {
    auto filter = new BinarizationFilter<DummyType, FakeImage<bool> >();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(BinarizationFilterTest, destinationImageTypeTemplateParameterExists) {
    auto filter = new BinarizationFilter<DummyType, FakeImage<bool>,
            FakeImage<DummyType> >();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(BinarizationFilterTest, defaultDestinationImageTypeIsSimpleArrayImage) {
    typedef BinarizationFilter<DummyType, FakeImage<bool> > implicitType;
    typedef BinarizationFilter<DummyType, FakeImage<bool>, Image<DummyType> >
            explicitType;

    EXPECT_TRUE((std::is_same<implicitType, explicitType>::value));
}

TEST(BinarizationFilterTest, classIsAFilter) {
    typedef Filter<DummyType, bool, FakeImage<bool> > filterType;
    typedef BinarizationFilter<DummyType, FakeImage<bool> >
            binarizationFilterType;

    EXPECT_TRUE((std::is_base_of<filterType, binarizationFilterType>::value));
}
