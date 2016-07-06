#ifndef FAKE_OPEN_C_L_IMAGE_HPP
#define FAKE_OPEN_C_L_IMAGE_HPP

#include "OpenCLImage.hpp"

template <typename PixelType>
class FakeOpenCLImage : public OpenCLImage<PixelType> {
private:
    using SuperClass = OpenCLImage<PixelType>;

public:
    static constexpr auto pixelBufferSize = SuperClass::pixelBufferSize;
};

#endif
