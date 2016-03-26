#ifndef OPEN_C_L_FILTER_HPP
#define OPEN_C_L_FILTER_HPP

#include <tuple>
#include <type_traits>

#include <CL/cl.hpp>

#include "AbstractFilter.hpp"
#include "OpenCLImage.hpp"

template <typename PixelType, typename... KernelParameterTypes>
class OpenCLFilter : public AbstractFilter<OpenCLImage<PixelType>,
        OpenCLImage<PixelType> > {
private:
    using ImageType = OpenCLImage<PixelType>;
    using SuperClass = AbstractFilter<ImageType, ImageType>;
    using TupleType = std::tuple<KernelParameterTypes...>;

    static constexpr auto numberOfExtraParameters =
            std::tuple_size<TupleType>::value;

private:
    const std::string kernelSourceCode;
    const std::string kernelFunctionName;

    TupleType kernelParameters;

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
        auto kernel = buildKernel(context);

        configureParameters(kernel, sourceImage, destinationImage);

        runKernel(kernel, sourceImage, destinationImage);
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

    void configureParameters(cl::Kernel& kernel, const ImageType& sourceImage,
            ImageType& destinationImage) {
        auto sourceImageBuffer = sourceImage.getImageBuffer();
        auto destinationImageBuffer = destinationImage.getImageBuffer();

        kernel.setArg(0, sourceImageBuffer);
        kernel.setArg(1, destinationImageBuffer);

        configureExtraParameters<0>(kernel);
    }

    template <int parameterIndex>
    typename std::enable_if<parameterIndex >= numberOfExtraParameters>::type
            configureExtraParameters(cl::Kernel&) {
    }

    template <int parameterIndex>
    typename std::enable_if<parameterIndex < numberOfExtraParameters>::type
            configureExtraParameters(cl::Kernel& kernel) {
        auto extraParameter = std::get<parameterIndex>(kernelParameters);

        kernel.setArg(parameterIndex + 2, extraParameter);

        configureExtraParameters<parameterIndex + 1>(kernel);
    }

    void runKernel(cl::Kernel& kernel, const ImageType& sourceImage,
            ImageType& destinationImage) {
        auto commandQueue = destinationImage.getCommandQueue();
        auto globalOffset = cl::NullRange;
        auto globalWorkSize = getGlobalWorkSize(sourceImage, destinationImage);

        commandQueue.enqueueNDRangeKernel(kernel, globalOffset, globalWorkSize);
    }
};

#endif
