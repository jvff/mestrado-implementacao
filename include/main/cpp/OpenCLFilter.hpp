#ifndef OPEN_C_L_FILTER_HPP
#define OPEN_C_L_FILTER_HPP

#include <tuple>

#include <CL/cl.hpp>

#include "AbstractFilter.hpp"
#include "OpenCLImage.hpp"

template <typename PixelType, typename... KernelParameterTypes>
class OpenCLFilter : public AbstractFilter<OpenCLImage<PixelType>,
        OpenCLImage<PixelType> > {
private:
    using ImageType = OpenCLImage<PixelType>;

private:
    const std::string kernelSourceCode;
    const std::string kernelFunctionName;

public:
    OpenCLFilter(const std::string& kernelSourceCode,
            const std::string& kernelFunctionName, KernelParameterTypes...)
            : kernelSourceCode(kernelSourceCode),
            kernelFunctionName(kernelFunctionName) {
    }

    void apply(const ImageType& sourceImage, ImageType& destinationImage)
            override {
        auto context = destinationImage.getContext();
        auto kernel = buildKernel(context);

        configureParameters(kernel, sourceImage, destinationImage);

        runKernel(kernel, destinationImage);
    }

protected:
    ImageType createDestinationImage(const ImageType& sourceImage) override {
        auto width = sourceImage.getWidth();
        auto height = sourceImage.getHeight();
        auto context = sourceImage.getContext();
        auto commandQueue = sourceImage.getCommandQueue();

        return ImageType(width, height, context, commandQueue);
    }

private:
    cl::Kernel buildKernel(cl::Context& context) {
        auto sourceCodeString = kernelSourceCode.c_str();
        auto sourceCodeSize = kernelSourceCode.length();
        auto sourcePair = std::make_pair(sourceCodeString, sourceCodeSize);
        auto sources = cl::Program::Sources(1, sourcePair);

        cl::Program program(context, sources);

        program.build();

        return cl::Kernel(program, kernelFunctionName.c_str());
    }

    void configureParameters(cl::Kernel& kernel, const ImageType& sourceImage,
            ImageType& destinationImage) {
        auto sourceImageBuffer = sourceImage.getImageBuffer();
        auto destinationImageBuffer = destinationImage.getImageBuffer();

        kernel.setArg(0, sourceImageBuffer);
        kernel.setArg(1, destinationImageBuffer);
    }

    void runKernel(cl::Kernel& kernel, ImageType& destinationImage) {
        auto commandQueue = destinationImage.getCommandQueue();
        auto width = destinationImage.getWidth();
        auto height = destinationImage.getHeight();
        auto globalOffset = cl::NullRange;
        auto globalWorkSize = cl::NDRange(width, height);

        commandQueue.enqueueNDRangeKernel(kernel, globalOffset, globalWorkSize);
    }
};

#endif
