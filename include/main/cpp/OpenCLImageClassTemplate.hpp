#ifndef OPEN_C_L_IMAGE_CLASS_TEMPLATE_HPP
#define OPEN_C_L_IMAGE_CLASS_TEMPLATE_HPP

#include <tuple>

#include <CL/cl.hpp>

#include "Image.hpp"
#include "OpenCLPixelTypeData.hpp"

#include "cl/ImagePixelTasks.h"

template <typename PixelType>
class OpenCLImage : public Image<PixelType> {
private:
    using PixelTypeData = OpenCLPixelTypeData<PixelType>;
    using SuperClass = Image<PixelType>;

    static constexpr unsigned int pixelSize = sizeof(PixelType);

private:
    cl::Context& context;
    cl::CommandQueue& commandQueue;
    cl::Image2D imageBuffer;
    cl::Program pixelPrograms;
    cl::Buffer pixelBuffer;

    using SuperClass::width;
    using SuperClass::height;

public:
    OpenCLImage(unsigned int width, unsigned int height,
            cl::Context& context, cl::CommandQueue& commandQueue)
            : SuperClass(width, height), context(context),
            commandQueue(commandQueue) {
        buildKernels();
        allocateBuffers();
    }

    cl::Context& getContext() const {
        return context;
    }

    cl::CommandQueue& getCommandQueue() const {
        return commandQueue;
    }

    const cl::Image2D getImageBuffer() const {
        return imageBuffer;
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        const auto& setPixelKernelName = PixelTypeData::setPixelKernel.c_str();

        cl::Kernel kernel(pixelPrograms, setPixelKernelName);

        kernel.setArg(0, imageBuffer);
        kernel.setArg(1, x);
        kernel.setArg(2, y);
        kernel.setArg(3, value);

        commandQueue.enqueueTask(kernel);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        const auto& getPixelKernelName = PixelTypeData::getPixelKernel.c_str();

        cl::Kernel kernel(pixelPrograms, getPixelKernelName);
        PixelType result;

        kernel.setArg(0, imageBuffer);
        kernel.setArg(1, x);
        kernel.setArg(2, y);
        kernel.setArg(3, pixelBuffer);

        commandQueue.enqueueTask(kernel);
        commandQueue.enqueueReadBuffer(pixelBuffer, CL_TRUE, 0, pixelSize,
                &result);

        return result;
    }

    using SuperClass::setPixel;
    using SuperClass::getPixel;
    using SuperClass::getPixelValue;
    using SuperClass::operator=;

private:
    void buildKernels() {
        auto& sourceCode = ImagePixelTasksSourceCode;
        auto sourceCodeSize = sizeof(ImagePixelTasksSourceCode);
        auto sourcePair = std::make_pair(sourceCode, sourceCodeSize);
        auto sources = cl::Program::Sources(1, sourcePair);
        auto compilerOptions = "-cl-std=CL2.0";

        pixelPrograms = cl::Program(context, sources);
        pixelPrograms.build(compilerOptions);
    }

    void allocateBuffers() {
        auto imageChannels = PixelTypeData::CL_PIXEL_CHANNELS;
        auto imageChannelType = PixelTypeData::CL_PIXEL_TYPE;
        auto imageFormat = cl::ImageFormat(imageChannels, imageChannelType);

        pixelBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, pixelSize);

        imageBuffer = cl::Image2D(context, CL_MEM_READ_WRITE, imageFormat,
                width, height);
    }
};

#endif
