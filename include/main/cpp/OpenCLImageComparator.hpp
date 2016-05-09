#ifndef OPEN_C_L_IMAGE_COMPARATOR_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_HPP

#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

#include "cl/ImageComparison.h"

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
            : SuperClass(ImageComparisonSourceCode, "compareImages",
                    &comparisonResult) {
    }

    bool imagesAreEqual(const ImageType& firstImage,
            const ImageType& secondImage) {
        if (dimensionsDontMatch(firstImage, secondImage))
            return false;

        auto& nonConstSecondImage = const_cast<ImageType&>(secondImage);

        comparisonResult = 0;

        SuperClass::apply(firstImage, nonConstSecondImage);

        return comparisonResult != 1;
    }

private:
    bool dimensionsDontMatch(const ImageType& firstImage,
            const ImageType& secondImage) {
        return firstImage.getWidth() != secondImage.getWidth()
            || firstImage.getHeight() != secondImage.getHeight();
    }
};

#endif
