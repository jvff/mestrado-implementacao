#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

#define TEST_C(testName) \
        TEST(BinarizationFilterOpenCLSpecializationsTest, testName)

TEST_C(hasSpecializationForDefaultComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(hasSpecializationForLessThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType, std::less>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(hasSpecializationForGreaterThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType,
            std::greater>;
    using ParentFilter = OpenCLFilter<PixelType, PixelType>;

    AssertThat<Specialization>::isSubClass(Of<ParentFilter>());
}

TEST_C(isConstructibleWithDefaultComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType>;
    using ThresholdParameter = const PixelType&;

    AssertThat<Specialization>::isConstructible(With<ThresholdParameter>());
}

TEST_C(isConstructibleWithLessThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType, std::less>;
    using ThresholdParameter = const PixelType&;

    AssertThat<Specialization>::isConstructible(With<ThresholdParameter>());
}

TEST_C(isConstructibleWithGreaterThanComparator) {
    using PixelType = int;
    using ImageType = OpenCLImage<PixelType>;
    using Specialization = BinarizationFilter<ImageType, ImageType,
            std::greater>;
    using ThresholdParameter = const PixelType&;

    AssertThat<Specialization>::isConstructible(With<ThresholdParameter>());
}
