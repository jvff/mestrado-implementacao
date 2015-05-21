#include <gtest/gtest.h>

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
