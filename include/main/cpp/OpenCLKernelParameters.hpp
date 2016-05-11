#ifndef OPEN_C_L_KERNEL_PARAMETERS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_HPP

#include <CL/cl.hpp>

template <typename... Parameters>
class OpenCLKernelParameters {
public:
    OpenCLKernelParameters(const cl::Context&, Parameters...) {
    }
};

#endif
