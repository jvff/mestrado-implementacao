#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLFilter.hpp"
#include "OpenCLImageComparator.hpp"

#include "DummyTypes.hpp"

TEST(OpenCLImageComparatorTest, classTemplateExists) {
    using ComparatorType = OpenCLImageComparator<DummyType>;

    AssertThat<ComparatorType>::isClassOrStruct();
}

TEST(OpenCLImageComparatorTest, isOpenCLFilter) {
    using ComparatorType = OpenCLImageComparator<DummyType>;
    using ParentClass = OpenCLFilter<DummyType, unsigned char*>;

    AssertThat<ComparatorType>::isSubClass(Of<ParentClass>());
}

TEST(OpenCLImageComparatorTest, hasDefaultConstructor) {
    using ComparatorType = OpenCLImageComparator<DummyType>;

    AssertThat<ComparatorType>::isConstructible(WithoutParameters());
}
