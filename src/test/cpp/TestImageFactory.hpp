#ifndef TEST_IMAGE_FACTORY_HPP
#define TEST_IMAGE_FACTORY_HPP

#include <vector>

#include <CL/cl.hpp>

#include "OpenCLImage.hpp"
#include "Image.hpp"

template <typename ImageType>
class TestImageFactory {
public:
    ImageType createImage(unsigned int width, unsigned int height) {
        return ImageType(width, height);
    }
};

template <typename PixelType>
class TestImageFactory<OpenCLImage<PixelType> > {
private:
    using ImageType = OpenCLImage<PixelType>;

    cl::Context context;
    cl::CommandQueue commandQueue;

public:
    TestImageFactory() {
        auto devices = getGpuDevices();

        createContext(devices);
        createCommandQueue(devices[0]);
    }

    ImageType createImage(unsigned int width, unsigned int height) {
        return ImageType(width, height, context, commandQueue);
    }

private:
    std::vector<cl::Device> getGpuDevices() {
        std::vector<cl::Device> devices;

        auto platforms = getPlatforms();
        auto firstPlatform = platforms[0];

        firstPlatform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

        return devices;
    }

    std::vector<cl::Platform> getPlatforms() {
        std::vector<cl::Platform> platforms;

        cl::Platform::get(&platforms);

        return platforms;
    }

    void createContext(const std::vector<cl::Device>& devices) {
        context = cl::Context(devices);
    }

    void createCommandQueue(const cl::Device& device) {
        commandQueue = cl::CommandQueue(context, device);
    }
};

#endif
