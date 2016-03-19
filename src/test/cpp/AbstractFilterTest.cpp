#include "AbstractFilterTest.hpp"

TEST_F(AbstractFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}
