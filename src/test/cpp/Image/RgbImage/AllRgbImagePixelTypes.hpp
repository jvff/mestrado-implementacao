#ifndef ALL_RGB_IMAGE_PIXEL_TYPES_HPP
#define ALL_RGB_IMAGE_PIXEL_TYPES_HPP

#include <cstdint>

#include <gtest/gtest.h>

using PixelTypes = ::testing::Types<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, char, short, int, long, long long,
        std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::int8_t,
        std::int16_t, std::int32_t, std::int64_t>;

#endif
