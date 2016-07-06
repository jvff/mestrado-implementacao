#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLPixelTypeData.hpp"

#define TEST_C(TypeName, Type, OpenCLPixelType, OpenCLPixelChannels, \
        OpenCLPixelBufferType, KernelSuffix, KernelPixelType) \
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
    TEST(OpenCLPixelTypeDataTest, hasPixelBufferSizeFor##TypeName) { \
        auto pixelChannels = OpenCLPixelTypeData<Type>::CL_PIXEL_BUFFER_SIZE; \
        \
        assertThat(pixelChannels).isEqualTo(sizeof(OpenCLPixelBufferType)); \
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

TEST_C(Bool, bool, CL_UNSIGNED_INT8, CL_R, cl_uchar, "ForBoolPixelType",
        "bool")
TEST_C(UnsignedChar, unsigned char, CL_UNSIGNED_INT8, CL_R, cl_uint,
        "UsingOneChannel", "uchar")
TEST_C(UnsignedInt, unsigned int, CL_UNSIGNED_INT32, CL_R, cl_uint,
        "UsingOneChannel", "uint")
TEST_C(UnsignedInt64, std::uint64_t, CL_UNSIGNED_INT32, CL_RG, cl_ulong,
        "UsingTwoChannels", "ulong")
TEST_C(Int, int, CL_SIGNED_INT32, CL_R, cl_uint, "UsingOneChannel", "int")
