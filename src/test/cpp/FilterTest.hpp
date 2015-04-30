#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "Filter.hpp"
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "VirtualDestructorTest.hpp"

class FilterTest : public testing::Test, protected VirtualDestructorTest {
protected:
    typedef Image<DummyTypes<1> > SourceImageType;
    typedef SimpleArrayImage<DummyTypes<2> > DestinationImageType;
    typedef Filter<SourceImageType, DestinationImageType> DummyFilter;
    typedef FakeFilter<SourceImageType, DestinationImageType> FakeDummyFilter;
};

#endif
