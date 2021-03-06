#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include <functional>

#include "Image.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"
#include "SimpleFilter.hpp"

#include "cl/BinarizationFilter.h"

template <typename SourceImageType, typename DestinationImageType,
        template <typename> class ComparatorTemplate = std::greater>
class BinarizationFilter : public SimpleFilter<SourceImageType,
        DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = SimpleFilter<SourceImageType, DestinationImageType>;
    using Comparator = ComparatorTemplate<SourcePixelType>;

    Comparator comparator;
    const SourcePixelType threshold;

public:
    using SuperClass::apply;

    BinarizationFilter(const SourcePixelType& parameter)
            : threshold(parameter) {
    }

protected:
    bool apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return comparator(sourceImage.getPixelValue(x, y), threshold);
    }
};

template <typename PixelType>
class BinarizationFilter<OpenCLImage<PixelType>, OpenCLImage<PixelType> >
        : public OpenCLFilter<PixelType, PixelType> {
private:
    using SuperClass = OpenCLFilter<PixelType, PixelType>;

public:
    BinarizationFilter(const PixelType& threshold)
            : SuperClass(BinarizationFilterSourceCode,
                    "binarizeUsingGreaterThan", threshold) {
    }
};

template <typename PixelType>
class BinarizationFilter<OpenCLImage<PixelType>, OpenCLImage<PixelType>,
        std::less> : public OpenCLFilter<PixelType, PixelType> {
private:
    using SuperClass = OpenCLFilter<PixelType, PixelType>;

public:
    BinarizationFilter(const PixelType& threshold)
            : SuperClass(BinarizationFilterSourceCode, "binarizeUsingLessThan",
                    threshold) {
    }
};

#endif
