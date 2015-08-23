#include "FilterTest.hpp"

TEST_F(FilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
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
