#include "HminMinTreeImplementationTest.hpp"

TEST_F(HminMinTreeImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(HminMinTreeImplementationTest, isFilterImplementation) {
    using ImplementationClass = DummyImplementation;
    using ParentImplementation = FilterImplementation<ImageType, ImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(HminMinTreeImplementationTest, isConstructibleWithParameters) {
    using FeatureHeightParameter = const PixelType&;
    using SourceImageParameter = const ImageType&;
    using DestinationImageParameter = ImageType&;

    AssertThat<DummyImplementation>::isConstructible(
            With<FeatureHeightParameter, SourceImageParameter,
                    DestinationImageParameter>());
}
