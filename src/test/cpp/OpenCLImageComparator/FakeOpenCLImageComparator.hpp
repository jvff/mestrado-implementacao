#ifndef FAKE_OPEN_C_L_IMAGE_COMPARATOR_HPP
#define FAKE_OPEN_C_L_IMAGE_COMPARATOR_HPP

#include "OpenCLImageComparator.hpp"

template <typename PixelType>
class FakeOpenCLImageComparator : public OpenCLImageComparator<PixelType> {
private:
    using SuperClass = OpenCLImageComparator<PixelType>;

public:
    using SuperClass::getGlobalWorkSize;
};

#endif
