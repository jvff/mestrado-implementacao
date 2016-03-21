#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

TEST(OpenCLPixelTypeDataTest, hasPixelTypeForUnsignedChar) {
    auto pixelType = OpenCLPixelTypeData<unsigned char>::CL_PIXEL_TYPE;

    assertThat(pixelType).isEqualTo(CL_UNSIGNED_INT8);
}
