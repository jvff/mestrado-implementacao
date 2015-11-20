#include "LuminanceFilterTest.hpp"

TEST_F(LuminanceFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(LuminanceFilterTest, isSubClassOfFilter) {
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}
