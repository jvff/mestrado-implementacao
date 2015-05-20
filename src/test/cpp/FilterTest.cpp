#include <fakeit.hpp>

#include "FilterTest.hpp"

TEST_F(FilterTest, classIsntAbstract) {
    auto filter = new FakeDummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST_F(FilterTest, destructorIsVirtual) {
    testIfDestructorIsVirtual<DummyFilter, FakeDummyFilter>();
}

TEST_F(FilterTest, imageFactoryWasCreated) {
    auto factory = fakeFilter.getImageFactory();

    EXPECT_TRUE(factory != NULL);
}

TEST_F(FilterTest, destinationImageDimensionsAreRequested) {
    expectImageCreation(1, 1);

    filter->apply(sourceImage);

    verifyImageWasCreated();
}

TEST_F(FilterTest, imageFactoryIsUsed) {
    DestinationImageType* result = NULL;

    expectImageCreation(2, 3);

    result = filter->apply(sourceImage);

    EXPECT_EQ(destinationImage, result);

    verifyImageWasCreated();
}
