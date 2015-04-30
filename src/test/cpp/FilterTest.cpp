
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
    auto fakeFilter = new FakeDummyFilter();
    auto factory = fakeFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete fakeFilter;
}
