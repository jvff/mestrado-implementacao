#ifndef PIXEL_TYPES_MACRO_HPP
#define PIXEL_TYPES_MACRO_HPP

#include <tuple>

#define PIXEL_TYPES(...) \
    using PixelTypesTuple = std::tuple<__VA_ARGS__>

#endif
