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
