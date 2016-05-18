#ifndef OPEN_C_L_KERNEL_PARAMETERS_FAKE_BUFFER_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_FAKE_BUFFER_HPP

#include <CL/cl.hpp>

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

#endif
