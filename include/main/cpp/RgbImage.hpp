#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include "Image.hpp"

template <typename InternalImageType>
class RgbImage : public Image<typename InternalImageType::PixelType> {
};

#endif
