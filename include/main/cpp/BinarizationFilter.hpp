#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include <functional>

#include "SimpleFilter.hpp"
#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType,
        template <typename> class ComparatorTemplate = std::less>
class BinarizationFilter : public SimpleFilter<SourceImageType,
        DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
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
        return comparator(sourceImage.getPixelValue(x, y), threshold);
    }
};

#endif
