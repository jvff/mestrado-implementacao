#ifndef BINARIZATION_FILTER_HPP
#define BINARIZATION_FILTER_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class BinarizationFilter : public Filter<SourcePixelType, bool,
        DestinationImageType, SourceImageType> {
private:
    typedef Filter<SourcePixelType, bool, DestinationImageType, SourceImageType>
            SuperClass;
public:
    using SuperClass::apply;

protected:
    unsigned int getDestinationImageWidth(const SourceImageType* sourceImage) {
        return sourceImage->getWidth();
    }

    unsigned int getDestinationImageHeight(const SourceImageType* sourceImage) {
        return sourceImage->getHeight();
    }

    bool apply(unsigned int, unsigned int, const SourceImageType*) {
        return true;
    }
};

#endif
