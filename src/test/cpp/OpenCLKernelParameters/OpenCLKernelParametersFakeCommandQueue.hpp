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

    using FakeReadOrWriteBufferCommand =
            FakeCommand<const FakeBuffer&, bool, std::size_t, std::size_t,
                    void*>;

    using FakeReadBufferCommand = FakeReadOrWriteBufferCommand;
    using FakeWriteBufferCommand = FakeReadOrWriteBufferCommand;

private:
    std::list<FakeReadBufferCommand> readBufferCommandList;
    std::list<FakeWriteBufferCommand> writeBufferCommandList;

public:
    cl_int enqueueReadBuffer(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        return enqueueBufferOperation(buffer, blocking, offset, size, address,
                readBufferCommandList);
    }

    cl_int enqueueWriteBuffer(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        return enqueueBufferOperation(buffer, blocking, offset, size, address,
                writeBufferCommandList);
    }

    void verifyReadCommand(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        verifyBufferCommand(buffer, blocking, offset, size, address,
                readBufferCommandList);
    }

    void verifyWriteCommand(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        verifyBufferCommand(buffer, blocking, offset, size, address,
                writeBufferCommandList);
    }

    template <typename... ParameterTypes>
    void verifyNonBlockingReadCommands(const ParameterTypes&... parameters) {
        verifyNonBlockingReadOrWriteCommands(readBufferCommandList,
                parameters...);
    }

    template <typename... ParameterTypes>
    void verifyNonBlockingWriteCommands(const ParameterTypes&... parameters) {
        verifyNonBlockingReadOrWriteCommands(writeBufferCommandList,
                parameters...);
    }

private:
    cl_int enqueueBufferOperation(const FakeBuffer& buffer, bool blocking,
            std::size_t offset, std::size_t size, void* address,
            std::list<FakeReadOrWriteBufferCommand>& commandList) {
        auto command = FakeReadOrWriteBufferCommand(buffer, blocking, offset,
                size, address);

        commandList.push_back(command);

        return CL_SUCCESS;
    }

    void verifyBufferCommand(const FakeBuffer& buffer, bool blocking,
            std::size_t offset, std::size_t size, void* address,
            std::list<FakeReadOrWriteBufferCommand>& commandList) {
        auto command = FakeReadOrWriteBufferCommand(buffer, blocking, offset,
                size, address);

        auto start = commandList.begin();
        auto end = commandList.end();

        auto searchResult = find(start, end, command);
        auto notFound = end;

        assertThat(searchResult).isNotEqualTo(notFound);
    }

    void verifyNonBlockingReadOrWriteCommands(
            std::list<FakeReadOrWriteBufferCommand>&) {
    }

    template <typename T, typename... RemainingTypes>
    void verifyNonBlockingReadOrWriteCommands(
            std::list<FakeReadOrWriteBufferCommand>& commandList,
            const T& value, const FakeBuffer& buffer,
            const RemainingTypes&... remainingParameters) {
        const auto nonBlocking = CL_FALSE;
        auto offset = 0;
        auto size = sizeof(value);
        void* address = (void*)&value;

        verifyBufferCommand(buffer, nonBlocking, offset, size, address,
                commandList);

        verifyNonBlockingReadOrWriteCommands(commandList,
                remainingParameters...);
    }
};

#endif
