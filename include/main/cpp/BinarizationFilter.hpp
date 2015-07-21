#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include "Filter.hpp"
#include "Image.hpp"

template <typename SourcePixelType, typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class BinarizationFilter : public Filter<SourcePixelType, bool,
        DestinationImageType, SourceImageType> {
private:
    typedef Filter<SourcePixelType, bool, DestinationImageType, SourceImageType>
            SuperClass;
    typedef std::function<bool(const SourcePixelType&, const SourcePixelType&)>
            Comparator;

    const SourcePixelType threshold;

public:
    using SuperClass::apply;

    BinarizationFilter(const SourcePixelType& parameter)
            : threshold(parameter) {
    }

    BinarizationFilter(const SourcePixelType& parameter, const Comparator&)
            : threshold(parameter) {
    }

protected:
    unsigned int getDestinationImageWidth(const SourceImageType& sourceImage) {
        return sourceImage.getWidth();
    }

    unsigned int getDestinationImageHeight(const SourceImageType& sourceImage) {
        return sourceImage.getHeight();
    }

    bool apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        return sourceImage.getPixel(x, y) >= threshold;
    }
};

#endif
