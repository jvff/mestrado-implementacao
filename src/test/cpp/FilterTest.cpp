#include "FilterTest.hpp"

TEST_F(FilterTest, classIsntAbstract) {
    AssertThat<FakeDummyFilter>::isConstructible(WithoutParameters());
}

TEST_F(FilterTest, destructorIsVirtual) {
    AssertThat<DummyFilter>::hasVirtualDestructor();
}

TEST_F(FilterTest, imageFactoryWasCreated) {
    auto factory = fakeFilter.getImageFactory();

    assertThat(factory).isNotNull();
}

TEST_F(FilterTest, destinationImageDimensionsAreRequested) {
    expectImageCreation(1, 1);

    filter.apply(sourceImage);

    verifyImageDimensionsWereRequested();
}

TEST_F(FilterTest, imageFactoryIsUsed) {
    DestinationImageType* result = NULL;

    expectImageCreation(2, 3);

    result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(destinationImage);

    verifyImageWasCreated();
}

TEST_F(FilterTest, callToApplyToTheCreatedImageWasPerformed) {
    expectImageCreation(5, 2);

    filter.apply(sourceImage);

    verifyApplyWasCalled();
}

TEST_F(FilterTest, filterWasAppliedToAllPixels) {
    expectImageCreation(10, 9);

    filter.apply(sourceImage);

    verifyApplyWasCalledOnEachPixel();
}

TEST_F(FilterTest, allPixelsWereSet) {
    expectImageCreation(3, 7);

    filter.apply(sourceImage);

    verifyAllPixelsWereSet();
}
