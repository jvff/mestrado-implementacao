
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "FilterTest.hpp"

typedef Image<DummyTypes<1> > SourceImageType;
typedef SimpleArrayImage<DummyTypes<2> > DestinationImageType;
typedef Filter<SourceImageType, DestinationImageType> DummyFilter;

TEST_F(FilterTest, classIsntAbstract) {
    DummyFilter* filter;

    filter = new FakeFilter<SourceImageType, DestinationImageType>();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST_F(FilterTest, destructorIsVirtual) {
    testIfDestructorIsVirtual<DummyFilter>();
}

TEST_F(FilterTest, imageFactoryWasCreated) {
    FakeFilter<SourceImageType, DestinationImageType>* mockFilter;
    ImageFactory<SimpleArrayImage<DummyTypes<2> > >* factory;

    mockFilter = new FakeFilter<SourceImageType, DestinationImageType>();
    factory = mockFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete mockFilter;
}
