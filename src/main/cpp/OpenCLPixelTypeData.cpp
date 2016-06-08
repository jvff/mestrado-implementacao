#include "OpenCLPixelTypeData.hpp"

#define OPENCL_PIXEL_TYPE_DATA_FOR(Type, KernelNameSuffix) \
const std::string OpenCLPixelTypeData<Type>::setPixelKernel \
        = "setPixel" KernelNameSuffix; \
\
const std::string OpenCLPixelTypeData<Type>::getPixelKernel \
        = "getPixel" KernelNameSuffix

OPENCL_PIXEL_TYPE_DATA_FOR(unsigned char, "UsingOneChannel");
OPENCL_PIXEL_TYPE_DATA_FOR(unsigned int, "UsingOneChannel");
OPENCL_PIXEL_TYPE_DATA_FOR(std::uint64_t, "UsingTwoChannels");
OPENCL_PIXEL_TYPE_DATA_FOR(int, "UsingOneChannel");
