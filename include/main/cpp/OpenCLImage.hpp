#ifndef OPEN_C_L_IMAGE_HPP
#define OPEN_C_L_IMAGE_HPP

#include <CL/cl.hpp>

#include "Image.hpp"

template <typename PixelType>
class OpenCLImage : public Image<PixelType> {
private:
    using SuperClass = Image<PixelType>;

public:
    OpenCLImage(unsigned int width, unsigned int height, cl::Context&,
            cl::CommandQueue&) : SuperClass(width, height) {
    }

    void setPixel(unsigned int, unsigned int, PixelType) override {
    }

    PixelType getPixelValue(unsigned int, unsigned int) const override {
        return 0;
    }
};

#endif
