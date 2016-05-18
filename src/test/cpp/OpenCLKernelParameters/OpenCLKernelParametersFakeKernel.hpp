#ifndef OPEN_C_L_KERNEL_PARAMETERS_FAKE_KERNEL_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_FAKE_KERNEL_HPP

#include <list>
#include <memory>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParametersWrapper.hpp"
#include "OpenCLKernelParametersWrapperFor.hpp"

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

#endif
