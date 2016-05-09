#ifndef OPEN_C_L_IMAGE_COMPARATOR_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_HPP

#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

template <typename PixelType>
class OpenCLImageComparator
        : protected OpenCLFilter<PixelType, unsigned char*> {
private:
    using ImageType = OpenCLImage<PixelType>;
    using SuperClass = OpenCLFilter<PixelType, unsigned char*>;

private:
    unsigned char comparisonResult;

public:
    OpenCLImageComparator()
            : SuperClass("", "compareImages", &comparisonResult) {
    }

    bool imagesAreEqual(const ImageType& firstImage,
            const ImageType& secondImage) {
        if (dimensionsDontMatch(firstImage, secondImage))
            return false;

        return true;
    }

private:
    bool dimensionsDontMatch(const ImageType& firstImage,
            const ImageType& secondImage) {
        return firstImage.getWidth() != secondImage.getWidth()
            || firstImage.getHeight() != secondImage.getHeight();
    }
};

#endif
