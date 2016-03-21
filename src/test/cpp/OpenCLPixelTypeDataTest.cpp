#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

TEST(OpenCLPixelTypeDataTest, hasPixelTypeForUnsignedChar) {
    auto pixelType = OpenCLPixelTypeData<unsigned char>::CL_PIXEL_TYPE;

    assertThat(pixelType).isEqualTo(CL_UNSIGNED_INT8);
}

TEST(OpenCLPixelTypeDataTest, hasPixelTypeForUnsignedInt) {
    auto pixelType = OpenCLPixelTypeData<unsigned int>::CL_PIXEL_TYPE;

    assertThat(pixelType).isEqualTo(CL_UNSIGNED_INT32);
}

TEST(OpenCLPixelTypeDataTest, hasPixelTypeForInt) {
    auto pixelType = OpenCLPixelTypeData<int>::CL_PIXEL_TYPE;

    assertThat(pixelType).isEqualTo(CL_SIGNED_INT32);
}
