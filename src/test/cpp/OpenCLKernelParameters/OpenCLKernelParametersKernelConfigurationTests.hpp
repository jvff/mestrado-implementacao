#ifndef OPEN_C_L_KERNEL_PARAMETERS_KERNEL_CONFIGURATION_TESTS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_KERNEL_CONFIGURATION_TESTS_HPP

#include <list>
#include <typeinfo>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParameters.hpp"

#include "OpenCLKernelParametersWrapper.hpp"

#define TEST_C(TestName) \
    TEST_F(OpenCLKernelParametersKernelConfigurationTests, TestName)

template <typename T>
class WrapperFor : public Wrapper {
private:
    T value;

public:
    WrapperFor(T value) : value(value) {
    }

    virtual bool operator==(const Wrapper& otherWrapper) const override {
        try {
            return *this == dynamic_cast<const WrapperFor<T>&>(otherWrapper);
        } catch (const std::bad_cast&) {
            return false;
        }
    }

    virtual bool operator==(const WrapperFor<T>& otherWrapper) const {
        return value == otherWrapper.value;
    }
};

class FakeBuffer {
private:
    const cl::Context& context;
    cl_mem_flags flags;
    std::size_t size;

public:
    FakeBuffer(const cl::Context& context, cl_mem_flags flags, std::size_t size)
            : context(context), flags(flags), size(size) {
    }

    bool operator==(const FakeBuffer& otherBuffer) const {
        return &context == &otherBuffer.context
            && flags == otherBuffer.flags
            && size == otherBuffer.size;
    }
};

class FakeKernel {
private:
    using WrapperPointer = std::shared_ptr<Wrapper>;

    using IndicesList = std::list<cl_uint>;
    using ValuesList = std::list<WrapperPointer>;

    using IndicesIterator = IndicesList::iterator;
    using ValuesIterator = ValuesList::iterator;

private:
    IndicesList indices;
    ValuesList values;

public:
    template <typename T>
    cl_int setArg(cl_uint index, T value) {
        auto wrappedValue = WrapperPointer(new WrapperFor<T>(value));

        indices.push_back(index);
        values.push_back(wrappedValue);

        return 0;
    }

    template <typename... ArgumentTypes>
    void verifyArguments(ArgumentTypes... arguments) {
        auto firstIndex = indices.begin();
        auto firstValue = values.begin();

        verifyArgumentsAt(firstIndex, firstValue, arguments...);
    }

private:
    void verifyArgumentsAt(IndicesIterator& indicesPosition,
            ValuesIterator& valuesPosition) {
        assertThat(indicesPosition).isEqualTo(indices.end());
        assertThat(valuesPosition).isEqualTo(values.end());
    }

    template <typename T, typename... RemainingArgumentTypes>
    void verifyArgumentsAt(IndicesIterator& indicesPosition,
            ValuesIterator& valuesPosition, unsigned int expectedIndex,
            T expectedValue, RemainingArgumentTypes... remainingArguments) {
        auto index = *indicesPosition;
        auto wrappedValue = *valuesPosition;
        auto& value = *wrappedValue;

        assertThat(index).isEqualTo(expectedIndex);
        assertThat(value).isEqualTo(WrapperFor<T>(expectedValue));

        ++indicesPosition;
        ++valuesPosition;

        verifyArgumentsAt(indicesPosition, valuesPosition,
                remainingArguments...);
    }
};

class OpenCLKernelParametersKernelConfigurationTests : public ::testing::Test {
protected:
    template <typename... ArgumentTypes>
    using TestOpenCLKernelParameters =
            TestableOpenCLKernelParameters<FakeKernel, FakeBuffer,
                    cl::CommandQueue, ArgumentTypes...>;

protected:
    cl::Context fakeContext;
    FakeKernel fakeKernel;
};

#endif
