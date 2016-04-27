#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLImageComparator.hpp"

#include "DummyTypes.hpp"

TEST(OpenCLImageComparatorTest, classTemplateExists) {
    using ComparatorType = OpenCLImageComparator<DummyType>;

    AssertThat<ComparatorType>::isClassOrStruct();
}
