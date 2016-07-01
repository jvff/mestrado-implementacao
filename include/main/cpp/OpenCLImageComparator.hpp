#ifndef OPEN_C_L_IMAGE_COMPARATOR_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_HPP

#include "OpenCLFilter.hpp"
#include "OpenCLImageClassTemplate.hpp"

#include "cl/ImageComparison.h"

template <typename PixelType>
class AbstractOpenCLImageComparator
        : protected OpenCLFilter<PixelType, unsigned char*> {
private:
    using SuperClass = OpenCLFilter<PixelType, unsigned char*>;

protected:
    using ImageType = OpenCLImage<PixelType>;

private:
    unsigned char comparisonResult;

public:
    AbstractOpenCLImageComparator()
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

template <typename PixelType>
class OpenCLImageComparator : public AbstractOpenCLImageComparator<PixelType> {
};

template <>
class OpenCLImageComparator<bool> : public AbstractOpenCLImageComparator<bool> {
protected:
    cl::NDRange getGlobalWorkSize(const ImageType&,
            const ImageType& destinationImage) const override {
        auto width = destinationImage.getWidth();
        auto height = destinationImage.getHeight();

        auto pixelGroupsPerLine = width / 8;

        return cl::NDRange(pixelGroupsPerLine, height);
    }
};

#endif
