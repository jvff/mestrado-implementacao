#ifndef ABSTRACT_OPEN_C_L_TEST_HPP
#define ABSTRACT_OPEN_C_L_TEST_HPP

#include <CL/cl.hpp>

#include <gtest/gtest.h>

class AbstractOpenCLTest : public ::testing::Test {
protected:
    static cl::Context context;
    static cl::CommandQueue commandQueue;

public:
    static void SetUpTestCase() {
        auto defaultDevice = cl::Device::getDefault();

        context = cl::Context::getDefault();
        commandQueue = cl::CommandQueue(context, defaultDevice);
    }
};

#endif
