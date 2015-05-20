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

    verifyImageDimensionsWereRequested();
}

TEST_F(FilterTest, imageFactoryIsUsed) {
    DestinationImageType* result = NULL;

    expectImageCreation(2, 3);

    result = filter->apply(sourceImage);

    EXPECT_EQ(destinationImage, result);

    verifyImageWasCreated();
}

TEST_F(FilterTest, callToApplyToTheCreatedImageWasPerformed) {
    expectImageCreation(5, 2);

    filter->apply(sourceImage);

    verifyApplyWasCalled();
}

TEST_F(FilterTest, filterWasAppliedToAllPixels) {
    expectImageCreation(10, 9);

    filter->apply(sourceImage);

    verifyApplyWasCalledOnEachPixel();
}
