#include "OpenCLImageComparatorBasicTests.hpp"

TEST_C(classTemplateExists) {
    AssertThat<ComparatorType>::isClassOrStruct();
}

TEST_C(isOpenCLFilter) {
    using ParentClass = OpenCLFilter<DummyType, unsigned char*>;

    AssertThat<ComparatorType>::isSubClass(Of<ParentClass>());
}

TEST_C(hasDefaultConstructor) {
    AssertThat<ComparatorType>::isConstructible(WithoutParameters());
}
