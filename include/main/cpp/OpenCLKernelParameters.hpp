#ifndef OPEN_C_L_KERNEL_PARAMETERS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_HPP

#include <tuple>

#include <CL/cl.hpp>

template <typename... Parameters>
class OpenCLKernelParameters {
private:
    using TupleType = std::tuple<Parameters...>;

    static constexpr unsigned int numberOfParameters =
            std::tuple_size<TupleType>::value;

    template <int parameterIndex>
    using EnableForValid =
            typename std::enable_if<parameterIndex < numberOfParameters>::type;

    template <int parameterIndex>
    using EnableForInvalid =
            typename std::enable_if<parameterIndex >= numberOfParameters>::type;

private:
    TupleType parameters;

public:
    OpenCLKernelParameters(const cl::Context&, Parameters... parameters)
            : parameters(parameters...) {
    }

    template <typename KernelType>
    void configureKernel(KernelType& kernel) {
        configureParameters<0>(kernel);
    }

private:
    template <int parameterIndex, typename KernelType>
    EnableForValid<parameterIndex> configureParameters(KernelType& kernel) {
        auto parameterValue = std::get<parameterIndex>(parameters);

        kernel.setArg(parameterIndex, parameterValue);
    }

    template <int parameterIndex, typename KernelType>
    EnableForInvalid<parameterIndex> configureParameters(KernelType&) {
    }
};

#endif
