#ifndef OPEN_C_L_IMAGE_HPP
#define OPEN_C_L_IMAGE_HPP

#include <CL/cl.hpp>

#include "Image.hpp"

template <typename PixelType>
class OpenCLImage : public Image<PixelType> {
private:
    using SuperClass = Image<PixelType>;

private:
    cl::Context& context;
    cl::CommandQueue& commandQueue;

public:
    OpenCLImage(unsigned int width, unsigned int height,
            cl::Context& context, cl::CommandQueue& commandQueue)
            : SuperClass(width, height), context(context),
            commandQueue(commandQueue) {
    }

    cl::Context& getContext() {
        return context;
    }

    cl::CommandQueue& getCommandQueue() {
        return commandQueue;
    }

    void setPixel(unsigned int, unsigned int, PixelType) override {
    }

    PixelType getPixelValue(unsigned int, unsigned int) const override {
        return 0;
    }
};

#endif
