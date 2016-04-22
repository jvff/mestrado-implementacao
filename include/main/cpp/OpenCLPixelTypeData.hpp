#ifndef OPEN_C_L_PIXEL_TYPE_DATA_HPP
#define OPEN_C_L_PIXEL_TYPE_DATA_HPP

#include <string>

#include <CL/cl.hpp>

template <typename PixelType>
struct OpenCLPixelTypeData {
};

#define OPENCL_PIXEL_TYPE_DATA_FOR(Type, OpenCLPixelType) \
template <> \
struct OpenCLPixelTypeData<Type> { \
    static constexpr auto CL_PIXEL_TYPE = OpenCLPixelType; \
    \
    static const std::string getPixelKernel; \
    static const std::string setPixelKernel; \
}

OPENCL_PIXEL_TYPE_DATA_FOR(unsigned char, CL_UNSIGNED_INT8);
OPENCL_PIXEL_TYPE_DATA_FOR(unsigned int, CL_UNSIGNED_INT32);
OPENCL_PIXEL_TYPE_DATA_FOR(int, CL_SIGNED_INT32);

#undef OPENCL_PIXEL_TYPE_DATA_FOR

#endif
