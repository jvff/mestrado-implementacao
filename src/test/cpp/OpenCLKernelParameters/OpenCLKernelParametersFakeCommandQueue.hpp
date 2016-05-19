#ifndef OPEN_C_L_KERNEL_PARAMETERS_FAKE_COMMAND_QUEUE_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_FAKE_COMMAND_QUEUE_HPP

#include <algorithm>
#include <list>
#include <tuple>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParametersFakeBuffer.hpp"

class FakeCommandQueue {
private:
    template <typename... ParameterTypes>
    class FakeCommand {
    private:
        std::tuple<ParameterTypes...> parameters;

    public:
        FakeCommand(ParameterTypes... parameters) : parameters(parameters...) {
        }

        bool operator==(const FakeCommand<ParameterTypes...>& other) {
            return parameters == other.parameters;
        }
    };

    using FakeReadBufferCommand =
            FakeCommand<const FakeBuffer&, cl_bool, std::size_t, std::size_t,
                    void*>;

    using FakeWriteBufferCommand =
            FakeCommand<const FakeBuffer&, cl_bool, std::size_t, std::size_t,
                    void*>;

private:
    std::list<FakeReadBufferCommand> readBufferCommandList;
    std::list<FakeWriteBufferCommand> writeBufferCommandList;

public:
    cl_int enqueueReadBuffer(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        auto command = FakeReadBufferCommand(buffer, blocking, offset, size,
                address);

        readBufferCommandList.push_back(command);

        return CL_SUCCESS;
    }

    cl_int enqueueWriteBuffer(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        auto command = FakeWriteBufferCommand(buffer, blocking, offset, size,
                address);

        writeBufferCommandList.push_back(command);

        return CL_SUCCESS;
    }

    void verifyReadCommand(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        auto command = FakeReadBufferCommand(buffer, blocking, offset, size,
                address);

        auto start = readBufferCommandList.begin();
        auto end = readBufferCommandList.end();

        auto searchResult = find(start, end, command);
        auto notFound = end;

        assertThat(searchResult).isNotEqualTo(notFound);
    }

    void verifyWriteCommand(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        auto command = FakeWriteBufferCommand(buffer, blocking, offset, size,
                address);

        auto start = writeBufferCommandList.begin();
        auto end = writeBufferCommandList.end();

        auto searchResult = find(start, end, command);
        auto notFound = end;

        assertThat(searchResult).isNotEqualTo(notFound);
    }

    void verifyNonBlockingReadCommands() {
    }

    template <typename T, typename... RemainingTypes>
    void verifyNonBlockingReadCommands(const T& value,
            const FakeBuffer& buffer,
            const RemainingTypes&... remainingParameters) {
        const auto nonBlocking = CL_FALSE;
        auto offset = 0;
        auto size = sizeof(value);
        void* address = (void*)&value;

        verifyReadCommand(buffer, nonBlocking, offset, size, address);

        verifyNonBlockingReadCommands(remainingParameters...);
    }

    void verifyNonBlockingWriteCommands() {
    }

    template <typename T, typename... RemainingTypes>
    void verifyNonBlockingWriteCommands(const T& value,
            const FakeBuffer& buffer,
            const RemainingTypes&... remainingParameters) {
        const auto nonBlocking = CL_FALSE;
        auto offset = 0;
        auto size = sizeof(value);
        void* address = (void*)&value;

        verifyWriteCommand(buffer, nonBlocking, offset, size, address);

        verifyNonBlockingWriteCommands(remainingParameters...);
    }
};

#endif
