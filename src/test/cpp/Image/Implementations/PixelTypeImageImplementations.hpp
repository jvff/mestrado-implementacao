#ifndef PIXEL_TYPE_IMAGE_IMPLEMENTATIONS_HPP
#define PIXEL_TYPE_IMAGE_IMPLEMENTATIONS_HPP

#include <type_traits>

#include "AbstractPixelTypeImageImplementations.hpp"

template <typename PixelType, typename Enable = void>
struct PixelTypeImageImplementations
        : public AbstractPixelTypeImageImplementations<PixelType> {
};

template <>
struct PixelTypeImageImplementations<bool>
        : public AbstractPixelTypeImageImplementations<bool, SimpleArrayImage,
                OpenCLImage> {
};

template <typename PixelType>
struct PixelTypeImageImplementations<PixelType,
        typename std::enable_if<std::is_integral<PixelType>::value>::type>
        : public AbstractPixelTypeImageImplementations<PixelType,
                SimpleArrayImage, OpenCLImage, MinTreeImageWithSimpleArrayImage,
                MaxTreeImageWithSimpleArrayImage> {
};

#endif
