#ifndef OPEN_C_L_FILTER_HPP
#define OPEN_C_L_FILTER_HPP

#include "AbstractFilter.hpp"
#include "OpenCLImage.hpp"

template <typename PixelType, typename... KernelParameterTypes>
class OpenCLFilter : public AbstractFilter<OpenCLImage<PixelType>,
        OpenCLImage<PixelType> > {
private:
    using ImageType = OpenCLImage<PixelType>;

public:
    OpenCLFilter(const std::string&, const std::string&,
            KernelParameterTypes...) {
    }

    void apply(const ImageType&, ImageType&) override {
    }

protected:
    ImageType createDestinationImage(const ImageType& sourceImage) override {
        auto width = sourceImage.getWidth();
        auto height = sourceImage.getHeight();
        auto context = sourceImage.getContext();
        auto commandQueue = sourceImage.getCommandQueue();

        return ImageType(width, height, context, commandQueue);
    }
};

#endif
