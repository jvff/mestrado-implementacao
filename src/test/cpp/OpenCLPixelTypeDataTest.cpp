#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

#define TEST_C(TypeName, Type, OpenCLPixelType, OpenCLPixelChannels, \
        KernelSuffix) \
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
    }

TEST_C(UnsignedChar, unsigned char, CL_UNSIGNED_INT8, CL_R, "UsingOneChannel")
TEST_C(UnsignedInt, unsigned int, CL_UNSIGNED_INT32, CL_R, "UsingOneChannel")
TEST_C(UnsignedInt64, std::uint64_t, CL_UNSIGNED_INT32, CL_RG,
        "UsingTwoChannels")
TEST_C(Int, int, CL_SIGNED_INT32, CL_R, "UsingOneChannel")
