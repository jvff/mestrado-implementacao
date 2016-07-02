#ifndef OPEN_C_L_FILTER_HPP
#define OPEN_C_L_FILTER_HPP

#include <CL/cl.hpp>

#include "AbstractFilter.hpp"
#include "OpenCLImageClassTemplate.hpp"
#include "OpenCLKernelParameters.hpp"

template <typename PixelType, typename... KernelParameterTypes>
class OpenCLFilter : public AbstractFilter<OpenCLImage<PixelType>,
        OpenCLImage<PixelType> > {
private:
    using ImageType = OpenCLImage<PixelType>;
    using SuperClass = AbstractFilter<ImageType, ImageType>;

private:
    const std::string kernelSourceCode;
    const std::string kernelFunctionName;

    OpenCLKernelParameters<KernelParameterTypes...> kernelParameters;

public:
    OpenCLFilter(const std::string& kernelSourceCode,
            const std::string& kernelFunctionName,
            const KernelParameterTypes&... kernelParameters)
            : kernelSourceCode(kernelSourceCode),
            kernelFunctionName(kernelFunctionName),
            kernelParameters(kernelParameters...) {
    }

    void apply(const ImageType& sourceImage, ImageType& destinationImage)
            override {
        auto& context = destinationImage.getContext();
        auto& commandQueue = destinationImage.getCommandQueue();
        auto kernel = buildKernel(context);

        configureParameters(context, kernel, sourceImage, destinationImage);

        kernelParameters.sendPointerData(commandQueue);
        runKernel(commandQueue, kernel, sourceImage, destinationImage);
        kernelParameters.retrievePointerData(commandQueue);

        commandQueue.finish();
    }

    using SuperClass::apply;

protected:
    ImageType createDestinationImage(const ImageType& sourceImage) override {
        auto width = sourceImage.getWidth();
        auto height = sourceImage.getHeight();
        auto& context = sourceImage.getContext();
        auto& commandQueue = sourceImage.getCommandQueue();

        return ImageType(width, height, context, commandQueue);
    }

    virtual cl::NDRange getGlobalWorkSize(const ImageType&,
            const ImageType& destinationImage) const {
        auto width = destinationImage.getWidth();
        auto height = destinationImage.getHeight();

        return cl::NDRange(width, height);
    }

    virtual cl::NDRange getLocalWorkSize(const ImageType&,
            const ImageType&) const {
        return cl::NullRange;
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

    void configureParameters(cl::Context& context, cl::Kernel& kernel,
            const ImageType& sourceImage, ImageType& destinationImage) {
        auto sourceImageBuffer = sourceImage.getImageBuffer();
        auto destinationImageBuffer = destinationImage.getImageBuffer();

        kernel.setArg(0, sourceImageBuffer);
        kernel.setArg(1, destinationImageBuffer);

        kernelParameters.configureKernel(context, kernel, 2u);
    }

    void runKernel(cl::CommandQueue& commandQueue, cl::Kernel& kernel,
            const ImageType& sourceImage, ImageType& destinationImage) {
        auto globalOffset = cl::NullRange;
        auto globalWorkSize = getGlobalWorkSize(sourceImage, destinationImage);
        auto localWorkSize = getLocalWorkSize(sourceImage, destinationImage);

        commandQueue.enqueueNDRangeKernel(kernel, globalOffset, globalWorkSize,
                localWorkSize);
    }
};

#endif
