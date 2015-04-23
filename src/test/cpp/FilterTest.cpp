#include <gtest/gtest.h>

#include "DummyFilter.hpp"

TEST(FilterTest, classIsntAbstract) {
    Filter<Image<DummyTypes<1> >, SimpleArrayImage<DummyTypes<2> > >* filter =
            new DummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(FilterTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyFilter* dummyFilter = new DummyFilter();
    Filter<Image<DummyTypes<1> >, SimpleArrayImage<DummyTypes<2> > >* filter
            = dummyFilter;

    dummyFilter->setDestructorListener(&destructorWasCalled);

    delete filter;

    EXPECT_TRUE(destructorWasCalled);
}

TEST(FilterTest, imageFactoryWasCreated) {
    DummyFilter* dummyFilter = new DummyFilter();
    ImageFactory<SimpleArrayImage<DummyTypes<2> > >* factory;

    factory = dummyFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete dummyFilter;
}
