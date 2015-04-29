#include <gtest/gtest.h>

#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DestructorInterceptorFor.hpp"
#include "DummyTypes.hpp"
#include "FakeFilter.hpp"

typedef Image<DummyTypes<1> > SourceImageType;
typedef SimpleArrayImage<DummyTypes<2> > DestinationImageType;
typedef Filter<SourceImageType, DestinationImageType> DummyFilter;

TEST(FilterTest, classIsntAbstract) {
    DummyFilter* filter;

    filter = new FakeFilter<SourceImageType, DestinationImageType>();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(FilterTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DestructorInterceptorFor<DummyFilter> *mockFilter;
    DummyFilter* filter;

    mockFilter = new DestructorInterceptorFor<DummyFilter>();
    filter = mockFilter;

    mockFilter->setDestructorListener(&destructorWasCalled);

    delete filter;

    EXPECT_TRUE(destructorWasCalled);
}

TEST(FilterTest, imageFactoryWasCreated) {
    FakeFilter<SourceImageType, DestinationImageType>* mockFilter;
    ImageFactory<SimpleArrayImage<DummyTypes<2> > >* factory;

    mockFilter = new FakeFilter<SourceImageType, DestinationImageType>();
    factory = mockFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete mockFilter;
}
