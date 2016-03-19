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
