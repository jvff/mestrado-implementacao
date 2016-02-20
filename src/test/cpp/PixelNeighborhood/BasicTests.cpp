#include "BasicTests.hpp"

TEST_C(classTemplateExists) {
    AssertThat<DummyPixelNeighborhood>::isClassOrStruct();
}

TEST_C(isConstructibleWithParameters) {
    AssertThat<DummyPixelNeighborhood>::isConstructible(WithoutParameters());
}
