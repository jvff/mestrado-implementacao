#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include "SimpleFilter.hpp"
#include "Image.hpp"

template <typename SourcePixelType, typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class BinarizationFilter : public SimpleFilter<SourceImageType,
        DestinationImageType> {
private:
    using SuperClass = SimpleFilter<SourceImageType, DestinationImageType>;
    using Comparator =
            std::function<bool(const SourcePixelType&, const SourcePixelType&)>;

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
    bool apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return comparator(sourceImage.getPixel(x, y), threshold);
    }
};

#endif
