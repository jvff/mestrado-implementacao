#include "AbstractFilterTest.hpp"

TEST_F(AbstractFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(AbstractFilterTest, destructorIsVirtual) {
    AssertThat<DummyFilter>::hasVirtualDestructor();
}
