#include "FilterTest.hpp"

TEST_F(FilterTest, classIsntAbstract) {
    AssertThat<FakeDummyFilter>::isConstructible(WithoutParameters());
}

TEST_F(FilterTest, destructorIsVirtual) {
    AssertThat<DummyFilter>::hasVirtualDestructor();
}

TEST_F(FilterTest, destinationImageDimensionsAreRequested) {
    expectImageCreation(1, 1);

    filter.apply(sourceImage);

    verifyImageDimensionsWereRequested();
}

TEST_F(FilterTest, imageCreationIsRequested) {
    expectImageCreation(2, 3);

    filter.apply(sourceImage);

    verifyImageWasCreated();
}

TEST_F(FilterTest, callToApplyToTheCreatedImageWasPerformed) {
    expectImageCreation(5, 2);

    auto result = filter.apply(sourceImage);

    verifyApplyWasCalled(result);
}

TEST_F(FilterTest, filterWasAppliedToAllPixels) {
    expectImageCreation(10, 9);

    filter.apply(sourceImage);

    verifyApplyWasCalledOnEachPixel();
}

TEST_F(FilterTest, allPixelsWereSet) {
    expectImageCreation(3, 7);

    auto result = filter.apply(sourceImage);

    verifyAllPixelsWereSet(result);
}
