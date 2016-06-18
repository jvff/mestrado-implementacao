#include "LuminanceFilterBasicTests.hpp"

TEST_C(classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_C(isSubClassOfFilter) {
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_C(rgbSpecializationIsSubClassOfSimpleFilter) {
    using SourcePixelType = unsigned char;
    using InternalImageType = Image<SourcePixelType>;
    using SourceImageType = RgbImage<InternalImageType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_C(specializationForOpenCLImagesIsSubClassOfOpenCLFilter) {
    using PixelType = unsigned char;
    using OpenCLImageType = OpenCLImage<PixelType>;
    using SourceImageType = OpenCLImageType;
    using DestinationImageType = OpenCLImageType;

    using FilterType = LuminanceFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = OpenCLFilter<PixelType>;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}

TEST_C(specializationForRgbOpenCLImagesIsSubClassOfFilter) {
    using PixelType = unsigned char;
    using OpenCLImageType = OpenCLImage<PixelType>;
    using SourceImageType = RgbImage<OpenCLImageType>;
    using DestinationImageType = OpenCLImageType;

    using FilterType = LuminanceFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = AbstractFilter<SourceImageType, DestinationImageType>;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}
