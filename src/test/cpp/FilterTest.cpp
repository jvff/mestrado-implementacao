
#include "FilterTest.hpp"

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
