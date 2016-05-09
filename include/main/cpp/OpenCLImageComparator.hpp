#ifndef OPEN_C_L_IMAGE_COMPARATOR_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_HPP

#include "OpenCLFilter.hpp"

template <typename PixelType>
class OpenCLImageComparator
        : protected OpenCLFilter<PixelType, unsigned char*> {
private:
    using SuperClass = OpenCLFilter<PixelType, unsigned char*>;

private:
    unsigned char comparisonResult;

public:
    OpenCLImageComparator()
            : SuperClass("", "compareImages", &comparisonResult) {
    }
};

#endif
