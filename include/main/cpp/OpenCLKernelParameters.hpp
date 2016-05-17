#ifndef OPEN_C_L_KERNEL_PARAMETERS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_HPP

#include <list>
#include <tuple>

#include <CL/cl.hpp>

template <typename KernelType, typename BufferType, typename CommandQueueType,
        typename... Parameters>
class TestableOpenCLKernelParameters {
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

    template <int parameterIndex>
    using ParameterType =
            typename std::tuple_element<parameterIndex, TupleType>::type;

    template <int parameterIndex>
    using ParameterIsPointer = std::is_pointer<ParameterType<parameterIndex> >;

    template <int parameterIndex>
    using EnableForPointerParameter =
            typename std::enable_if<ParameterIsPointer<parameterIndex>::value,
                    BufferType>::type;

    template <int parameterIndex>
    using EnableForNonPointerParameter =
            typename std::enable_if<!ParameterIsPointer<parameterIndex>::value,
                    ParameterType<parameterIndex> >::type;

    struct PointerData {
        BufferType deviceBuffer;
        std::size_t dataSize;
        void* hostAddress;
    };

private:
    const cl::Context& context;
    TupleType parameters;
    std::list<PointerData> pointerDataList;

public:
    TestableOpenCLKernelParameters(const cl::Context& context,
            Parameters... parameters)
            : context(context), parameters(parameters...) {
    }

    void configureKernel(KernelType& kernel) {
        configureParameters<0>(kernel);
    }

    void sendPointerData(CommandQueueType& commandQueue) {
        for (auto& pointerData : pointerDataList)
            sendData(commandQueue, pointerData);
    }

private:
    template <int parameterIndex>
    EnableForValid<parameterIndex> configureParameters(KernelType& kernel) {
        const auto nextParameterIndex = parameterIndex + 1;
        auto parameterValue = getParameter<parameterIndex>();

        kernel.setArg(parameterIndex, parameterValue);

        configureParameters<nextParameterIndex>(kernel);
    }

    template <int parameterIndex>
    EnableForInvalid<parameterIndex> configureParameters(KernelType&) {
    }

    template <int parameterIndex>
    EnableForPointerParameter<parameterIndex> getParameter() {
        using PointerType = ParameterType<parameterIndex>;
        using ValueType = typename std::remove_pointer<PointerType>::type;

        auto size = sizeof(ValueType);
        auto buffer = BufferType(context, CL_MEM_READ_WRITE, size);
        auto address = std::get<parameterIndex>(parameters);

        pointerDataList.push_back(PointerData{ buffer, size, address });

        return buffer;
    }

    template <int parameterIndex>
    EnableForNonPointerParameter<parameterIndex> getParameter() {
        return std::get<parameterIndex>(parameters);
    }

    void sendData(CommandQueueType& commandQueue, PointerData& pointerData) {
        constexpr auto nonBlocking = CL_FALSE;

        auto& buffer = pointerData.deviceBuffer;
        auto size = pointerData.dataSize;
        auto* address = pointerData.hostAddress;

        commandQueue.enqueueWriteBuffer(buffer, nonBlocking, 0, size, address);
    }
};

template <typename... ParameterTypes>
using OpenCLKernelParameters =
        TestableOpenCLKernelParameters<cl::Kernel, cl::Buffer, cl::CommandQueue,
                ParameterTypes...>;

#endif
