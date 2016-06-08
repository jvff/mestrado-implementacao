#include "OpenCLPixelTypeData.hpp"

#define OPENCL_PIXEL_TYPE_DATA_FOR(Type, KernelNameSuffix, KernelPixelType) \
const std::string OpenCLPixelTypeData<Type>::setPixelKernel \
        = "setPixel" KernelNameSuffix; \
\
const std::string OpenCLPixelTypeData<Type>::getPixelKernel \
        = "getPixel" KernelNameSuffix; \
\
const std::string OpenCLPixelTypeData<Type>::kernelPixelType \
        = KernelPixelType

OPENCL_PIXEL_TYPE_DATA_FOR(unsigned char, "UsingOneChannel", "uchar");
OPENCL_PIXEL_TYPE_DATA_FOR(unsigned int, "UsingOneChannel", "uint");
OPENCL_PIXEL_TYPE_DATA_FOR(std::uint64_t, "UsingTwoChannels", "ulong");
OPENCL_PIXEL_TYPE_DATA_FOR(int, "UsingOneChannel", "int");
