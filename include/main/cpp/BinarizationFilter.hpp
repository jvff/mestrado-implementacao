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

    static bool defaultComparator(const SourcePixelType& value,
            const SourcePixelType& threshold) {
        return value >= threshold;
    }

    Comparator comparator;
    const SourcePixelType threshold;

public:
    using SuperClass::apply;

    BinarizationFilter(const SourcePixelType& parameter)
            : BinarizationFilter(parameter, defaultComparator) {
    }

    BinarizationFilter(const SourcePixelType& parameter,
            const Comparator& customComparator) : comparator(customComparator),
            threshold(parameter) {
    }

protected:
    unsigned int getDestinationImageWidth(const SourceImageType& sourceImage)
            override {
        return sourceImage.getWidth();
    }

    unsigned int getDestinationImageHeight(const SourceImageType& sourceImage)
            override {
        return sourceImage.getHeight();
    }

    bool apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return comparator(sourceImage.getPixel(x, y), threshold);
    }
};

#endif
