#ifndef OPEN_C_L_KERNEL_PARAMETERS_FAKE_COMMAND_QUEUE_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_FAKE_COMMAND_QUEUE_HPP

#include <algorithm>
#include <list>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParametersFakeBuffer.hpp"

class FakeWriteBufferCommand {
private:
    const FakeBuffer& buffer;
    cl_bool blocking;
    std::size_t offset;
    std::size_t size;
    void* address;

public:
    FakeWriteBufferCommand(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address)
            : buffer(buffer), blocking(blocking), offset(offset), size(size),
            address(address) {
    }

    bool operator==(const FakeWriteBufferCommand& other) {
        return buffer == other.buffer
            && blocking == other.blocking
            && offset == other.offset
            && size == other.size
            && address == other.address;
    }
};

class FakeCommandQueue {
private:
    std::list<FakeWriteBufferCommand> writeBufferCommandList;

public:
    cl_int enqueueWriteBuffer(const FakeBuffer& buffer, cl_bool blocking,
            std::size_t offset, std::size_t size, void* address) {
        auto command = FakeWriteBufferCommand(buffer, blocking, offset, size,
                address);

        writeBufferCommandList.push_back(command);

        return CL_SUCCESS;
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
