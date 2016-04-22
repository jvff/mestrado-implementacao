#include "OpenCLPixelTypeData.hpp"

const std::string OpenCLPixelTypeData<unsigned char>::setPixelKernel
        = "setPixelUsingOneChannel";

const std::string OpenCLPixelTypeData<unsigned int>::setPixelKernel
        = "setPixelUsingOneChannel";

const std::string OpenCLPixelTypeData<int>::setPixelKernel
        = "setPixelUsingOneChannel";
