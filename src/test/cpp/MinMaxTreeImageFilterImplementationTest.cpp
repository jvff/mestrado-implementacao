#include "MinMaxTreeImageFilterImplementationTest.hpp"

TEST_F(MinMaxTreeImageFilterImplementationTest, classTemplateExists) {
    AssertThat<ImplementationType>::isClassOrStruct();
}

TEST_F(MinMaxTreeImageFilterImplementationTest, isFilterImplementation) {
    using ParentImplementationType = FilterImplementation<ImageType, ImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<ParentImplementationType>());
}
