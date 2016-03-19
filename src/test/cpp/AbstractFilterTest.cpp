#include "AbstractFilterTest.hpp"

TEST_F(AbstractFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(AbstractFilterTest, destructorIsVirtual) {
    AssertThat<DummyFilter>::hasVirtualDestructor();
}

TEST_F(AbstractFilterTest, imageCreationIsRequested) {
    expectImageCreation(7, 4);

    filter.apply(sourceImage);

    verifyImageWasCreated();
}

TEST_F(AbstractFilterTest, callsApplyWithTheCreatedImage) {
    expectImageCreation(43, 84);

    auto result = filter.apply(sourceImage);

    verifyApplyWasCalled(result);
}
