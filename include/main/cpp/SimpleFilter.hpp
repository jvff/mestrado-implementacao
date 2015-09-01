#ifndef SIMPLE_FILTER_HPP
#define SIMPLE_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class SimpleFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                auto newPixel = apply(x, y, sourceImage);

                destinationImage.setPixel(x, y, newPixel);
            }
        }
    }

    using SuperClass::apply;

protected:
    virtual DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) = 0;
};

#endif
