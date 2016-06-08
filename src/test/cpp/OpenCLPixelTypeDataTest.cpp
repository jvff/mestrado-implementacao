#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

#define TEST_C(TypeName, Type, OpenCLPixelType, OpenCLPixelChannels, \
        KernelSuffix, KernelPixelType) \
    TEST(OpenCLPixelTypeDataTest, hasPixelTypeFor##TypeName) { \
        auto pixelType = OpenCLPixelTypeData<Type>::CL_PIXEL_TYPE; \
        \
        assertThat(pixelType).isEqualTo(OpenCLPixelType); \
    } \
    \
    TEST(OpenCLPixelTypeDataTest, hasPixelChannelsFor##TypeName) { \
        auto pixelChannels = OpenCLPixelTypeData<Type>::CL_PIXEL_CHANNELS; \
        \
        assertThat(pixelChannels).isEqualTo(OpenCLPixelChannels); \
    } \
    \
    TEST(OpenCLPixelTypeDataTest, hasSetPixelKernelFor##TypeName) { \
        auto setPixelKernel = OpenCLPixelTypeData<Type>::setPixelKernel; \
        \
        assertThat(setPixelKernel).isEqualTo("setPixel" KernelSuffix); \
    } \
    \
    TEST(OpenCLPixelTypeDataTest, hasGetPixelKernelFor##TypeName) { \
        auto getPixelKernel = OpenCLPixelTypeData<Type>::getPixelKernel; \
        \
        assertThat(getPixelKernel).isEqualTo("getPixel" KernelSuffix); \
    } \
    \
    TEST(OpenCLPixelTypeDataTest, hasKernelPixelTypeFor##TypeName) { \
        auto kernelPixelType = OpenCLPixelTypeData<Type>::kernelPixelType; \
        \
        assertThat(kernelPixelType).isEqualTo(KernelPixelType); \
    }

TEST_C(UnsignedChar, unsigned char, CL_UNSIGNED_INT8, CL_R, "UsingOneChannel",
        "uchar")
TEST_C(UnsignedInt, unsigned int, CL_UNSIGNED_INT32, CL_R, "UsingOneChannel",
        "uint")
TEST_C(UnsignedInt64, std::uint64_t, CL_UNSIGNED_INT32, CL_RG,
        "UsingTwoChannels", "ulong")
TEST_C(Int, int, CL_SIGNED_INT32, CL_R, "UsingOneChannel", "int")
