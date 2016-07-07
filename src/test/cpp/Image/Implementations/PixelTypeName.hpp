#ifndef PIXEL_TYPE_NAME_HPP
#define PIXEL_TYPE_NAME_HPP

#include <cstdint>

#define PIXEL_TYPE_NAME(Type) \
template <typename Enable> \
struct PixelTypeName<Type, Enable> { \
    static const char* name; \
}; \
\
template <typename Enable> \
const char* PixelTypeName<Type, Enable>::name = #Type

template <typename T, typename Enable = void>
struct PixelTypeName {
};

PIXEL_TYPE_NAME(bool);
PIXEL_TYPE_NAME(unsigned char);
PIXEL_TYPE_NAME(std::uint64_t);
PIXEL_TYPE_NAME(int);

#endif
