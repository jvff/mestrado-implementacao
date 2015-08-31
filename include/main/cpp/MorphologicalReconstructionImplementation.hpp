#ifndef MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class MorphologicalReconstructionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

public:
    MorphologicalReconstructionImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
    }
};

#endif
