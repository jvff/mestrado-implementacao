#ifndef OPEN_C_L_PIXEL_TYPE_DATA_HPP
#define OPEN_C_L_PIXEL_TYPE_DATA_HPP

#include <cstdint>
#include <string>

#include <CL/cl.hpp>

template <typename PixelType>
struct OpenCLPixelTypeData {
};

#define OPENCL_PIXEL_TYPE_DATA_FOR(Type, OpenCLPixelType, OpenCLPixelChannels, \
        PixelBufferType) \
template <> \
struct OpenCLPixelTypeData<Type> { \
    using OpenCLPixelBufferType = PixelBufferType; \
    \
    static constexpr auto CL_PIXEL_TYPE = OpenCLPixelType; \
    static constexpr auto CL_PIXEL_CHANNELS = OpenCLPixelChannels; \
    static constexpr auto CL_PIXEL_BUFFER_SIZE = \
            sizeof(OpenCLPixelBufferType); \
    \
    static const std::string getPixelKernel; \
    static const std::string setPixelKernel; \
    static const std::string kernelPixelType; \
}

OPENCL_PIXEL_TYPE_DATA_FOR(bool, CL_UNSIGNED_INT8, CL_R, cl_uchar);
OPENCL_PIXEL_TYPE_DATA_FOR(unsigned char, CL_UNSIGNED_INT8, CL_R, cl_uint);
OPENCL_PIXEL_TYPE_DATA_FOR(unsigned int, CL_UNSIGNED_INT32, CL_R, cl_uint);
OPENCL_PIXEL_TYPE_DATA_FOR(std::uint64_t, CL_UNSIGNED_INT32, CL_RG, cl_ulong);
OPENCL_PIXEL_TYPE_DATA_FOR(int, CL_SIGNED_INT32, CL_R, cl_uint);

#undef OPENCL_PIXEL_TYPE_DATA_FOR

#endif
