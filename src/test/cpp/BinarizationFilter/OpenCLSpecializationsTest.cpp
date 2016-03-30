#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

#include "BinarizationFilterTest.hpp"

TEST_C(OpenCLSpecializationsTest, hasSpecializationForDefaultComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(OpenCLSpecializationsTest, hasSpecializationForLessThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType, std::less>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(OpenCLSpecializationsTest, hasSpecializationForGreaterThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType,
            std::greater>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(OpenCLSpecializationsTest, isConstructibleWithDefaultComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType>;
    using ThresholdParameter = const PixelType&;

    AssertThat<Specialization>::isConstructible(With<ThresholdParameter>());
}

TEST_C(OpenCLSpecializationsTest, isConstructibleWithLessThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType, std::less>;
    using ThresholdParameter = const PixelType&;

    AssertThat<Specialization>::isConstructible(With<ThresholdParameter>());
}
