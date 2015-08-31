#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_HPP

#include "ComplexFilter.hpp"
#include "MorphologicalReconstructionImplementation.hpp"

template <typename PixelType, class DestinationImageType,
        class SourceImageType = Image<PixelType> >
class MorphologicalReconstructionFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, MorphologicalReconstructionImplementation<
                SourceImageType, DestinationImageType> > {
private:
    using ParentFilter = Filter<PixelType, PixelType, DestinationImageType,
            SourceImageType>;

public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        using ImplementationType = MorphologicalReconstructionImplementation<
                SourceImageType, DestinationImageType>;

        ImplementationType(sourceImage, destinationImage).apply();
    }
};

#endif
