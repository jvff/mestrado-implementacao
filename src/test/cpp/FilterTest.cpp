#include <gtest/gtest.h>

#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "MockFilter.hpp"

typedef Image<DummyTypes<1> > SourceImageType;
typedef SimpleArrayImage<DummyTypes<2> > DestinationImageType;
typedef Filter<SourceImageType, DestinationImageType> DummyFilter;

TEST(FilterTest, classIsntAbstract) {
    DummyFilter* filter;

    filter = new MockFilter<SourceImageType, DestinationImageType>();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(FilterTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    MockFilter<SourceImageType, DestinationImageType>* mockFilter;
    DummyFilter* filter;

    mockFilter = new MockFilter<SourceImageType, DestinationImageType>();
    filter = mockFilter;

    mockFilter->setDestructorListener(&destructorWasCalled);

    delete filter;

    EXPECT_TRUE(destructorWasCalled);
}

TEST(FilterTest, imageFactoryWasCreated) {
    MockFilter<SourceImageType, DestinationImageType>* mockFilter;
    ImageFactory<SimpleArrayImage<DummyTypes<2> > >* factory;

    mockFilter = new MockFilter<SourceImageType, DestinationImageType>();
    factory = mockFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete mockFilter;
}
