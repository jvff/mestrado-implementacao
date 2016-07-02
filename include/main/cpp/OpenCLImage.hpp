#ifndef OPEN_C_L_IMAGE_HPP
#define OPEN_C_L_IMAGE_HPP

#include "OpenCLImageClassTemplate.hpp"
#include "OpenCLImageComparator.hpp"

template <typename PixelType>
bool operator==(const OpenCLImage<PixelType>& firstImage,
        const OpenCLImage<PixelType>& secondImage) {
    auto comparator = OpenCLImageComparator<PixelType>();

    return comparator.imagesAreEqual(firstImage, secondImage);
}

#endif
