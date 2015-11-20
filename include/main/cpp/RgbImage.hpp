#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include <type_traits>

#include "Image.hpp"

template <typename InternalImageType>
class RgbImage : public Image<typename InternalImageType::PixelType> {
private:
    using PixelType = typename InternalImageType::PixelType;

    static constexpr bool pixelTypeIsSupported() {
        return std::is_integral<PixelType>::value
            && !std::is_same<PixelType, bool>::value;
    }

    static_assert(pixelTypeIsSupported(), "Unsupported pixel type");

public:
    RgbImage(InternalImageType&) {
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return 0;
    }
};

#endif
