#ifndef OPEN_C_L_PIXEL_TYPE_DATA_HPP
#define OPEN_C_L_PIXEL_TYPE_DATA_HPP

template <typename PixelType>
struct OpenCLPixelTypeData {
};

template <>
struct OpenCLPixelTypeData<unsigned char> {
    static constexpr auto CL_PIXEL_TYPE = CL_UNSIGNED_INT8;
};

template <>
struct OpenCLPixelTypeData<unsigned int> {
    static constexpr auto CL_PIXEL_TYPE = CL_UNSIGNED_INT32;
};

template <>
struct OpenCLPixelTypeData<int> {
    static constexpr auto CL_PIXEL_TYPE = CL_SIGNED_INT32;
};

#endif
