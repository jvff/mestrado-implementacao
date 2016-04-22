#ifndef OPEN_C_L_PIXEL_TYPE_DATA_HPP
#define OPEN_C_L_PIXEL_TYPE_DATA_HPP

#include <string>

#include <CL/cl.hpp>

template <typename PixelType>
struct OpenCLPixelTypeData {
};

template <>
struct OpenCLPixelTypeData<unsigned char> {
    static constexpr auto CL_PIXEL_TYPE = CL_UNSIGNED_INT8;

    static const std::string setPixelKernel;
};

template <>
struct OpenCLPixelTypeData<unsigned int> {
    static constexpr auto CL_PIXEL_TYPE = CL_UNSIGNED_INT32;

    static const std::string setPixelKernel;
};

template <>
struct OpenCLPixelTypeData<int> {
    static constexpr auto CL_PIXEL_TYPE = CL_SIGNED_INT32;

    static const std::string setPixelKernel;
};

#endif
