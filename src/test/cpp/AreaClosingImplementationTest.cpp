#include "AreaClosingImplementationTest.hpp"

TEST_F(AreaClosingImplementationTest, classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}
