#ifndef OPEN_C_L_FILTER_ON_IMAGE_QUARTERS_HPP
#define OPEN_C_L_FILTER_ON_IMAGE_QUARTERS_HPP

#include <CL/cl.hpp>

#include "OpenCLFilter.hpp"

template <typename PixelType, typename... KernelParameters>
class OpenCLFilterOnImageQuarters
        : public OpenCLFilter<PixelType, KernelParameters...> {
private:
    using ImageType = OpenCLImage<PixelType>;
    using SuperClass = OpenCLFilter<PixelType, KernelParameters...>;

public:
    using SuperClass::SuperClass;

protected:
    cl::NDRange getLocalWorkSize(const ImageType&,
            const ImageType& destinationImage) const override {
        auto width = destinationImage.getWidth();
        auto height = destinationImage.getHeight();

        return cl::NDRange(width / 2, height / 2);
    }
};

#endif
