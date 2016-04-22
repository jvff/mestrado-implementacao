#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

#define TEST_C(TypeName, Type, OpenCLPixelType, KernelSuffix) \
    TEST(OpenCLPixelTypeDataTest, hasPixelTypeFor##TypeName) { \
        auto pixelType = OpenCLPixelTypeData<Type>::CL_PIXEL_TYPE; \
        \
        assertThat(pixelType).isEqualTo(OpenCLPixelType); \
    } \
    \
    TEST(OpenCLPixelTypeDataTest, hasSetPixelKernelFor##TypeName) { \
        auto setPixelKernel = OpenCLPixelTypeData<Type>::setPixelKernel; \
        \
        assertThat(setPixelKernel).isEqualTo("setPixel" KernelSuffix); \
    }

TEST_C(UnsignedChar, unsigned char, CL_UNSIGNED_INT8, "UsingOneChannel")
TEST_C(UnsignedInt, unsigned int, CL_UNSIGNED_INT32, "UsingOneChannel")
TEST_C(Int, int, CL_SIGNED_INT32, "UsingOneChannel")
