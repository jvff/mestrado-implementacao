#include "OpenCLFilterTest.hpp"

TEST_F(OpenCLFilterTest, classTemplateExists) {
    AssertThat<FilterType>::isClassOrStruct();
}
