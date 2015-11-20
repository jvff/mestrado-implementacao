#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include <type_traits>

#include "Image.hpp"

template <typename InternalImageType>
class RgbImage : public Image<typename InternalImageType::PixelType> {
private:
    using PixelType = typename InternalImageType::PixelType;
    using SuperClass = Image<PixelType>;

    static constexpr bool pixelTypeIsSupported() {
        return std::is_integral<PixelType>::value
            && !std::is_same<PixelType, bool>::value;
    }

    static_assert(pixelTypeIsSupported(), "Unsupported pixel type");

private:
    InternalImageType& internalImage;

public:
    RgbImage(InternalImageType& internalImage)
            : SuperClass(internalImage.getWidth(), internalImage.getHeight()),
            internalImage(internalImage) {
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    using SuperClass::operator=;
};

#endif
