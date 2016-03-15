#ifndef OPEN_C_L_IMAGE_HPP
#define OPEN_C_L_IMAGE_HPP

#include <tuple>

#include <CL/cl.hpp>

#include "Image.hpp"

#include "cl/ImagePixelTasks.h"

template <typename PixelType>
class OpenCLImage : public Image<PixelType> {
private:
    using SuperClass = Image<PixelType>;

private:
    cl::Context& context;
    cl::CommandQueue& commandQueue;
    cl::Image2D imageBuffer;
    cl::Program pixelPrograms;

public:
    OpenCLImage(unsigned int width, unsigned int height,
            cl::Context& context, cl::CommandQueue& commandQueue)
            : SuperClass(width, height), context(context),
            commandQueue(commandQueue) {
        auto& sourceCode = ImagePixelTasksSourceCode;
        auto sourceCodeSize = sizeof(ImagePixelTasksSourceCode);
        auto sourcePair = std::make_pair(sourceCode, sourceCodeSize);
        auto sources = cl::Program::Sources(1, sourcePair);

        pixelPrograms = cl::Program(context, sources);
        pixelPrograms.build();

        auto imageFormat = cl::ImageFormat(CL_R, CL_UNSIGNED_INT32);

        imageBuffer = cl::Image2D(context, CL_MEM_READ_WRITE, imageFormat,
                width, height);
    }

    cl::Context& getContext() {
        return context;
    }

    cl::CommandQueue& getCommandQueue() {
        return commandQueue;
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        cl::Kernel kernel(pixelPrograms, "setPixel");

        kernel.setArg(0, imageBuffer);
        kernel.setArg(1, x);
        kernel.setArg(2, y);
        kernel.setArg(3, value);

        commandQueue.enqueueTask(kernel);
    }

    PixelType getPixelValue(unsigned int, unsigned int) const override {
        return 0;
    }

    using SuperClass::setPixel;
    using SuperClass::getPixel;
    using SuperClass::getPixelValue;
};

#endif
