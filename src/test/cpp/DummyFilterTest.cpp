#include <gtest/gtest.h>

#include "Filter.hpp"
#include "Image.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

typedef DestructorInterceptor<
	    Filter<Image<DummyTypes<1> >, Image<DummyTypes<2> > > > DummyFilter;

TEST(DummyFilterTest, classIsntAbstract) {
    Filter<Image<DummyTypes<1> >, Image<DummyTypes<2> > >* filter =
	    new DummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(DummyFilterTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyFilter* dummyFilter = new DummyFilter();
    Filter<Image<DummyTypes<1> >, Image<DummyTypes<2> > >* filter = dummyFilter;

    dummyFilter->setDestructorListener(&destructorWasCalled);

    delete filter;

    EXPECT_TRUE(destructorWasCalled);
}
