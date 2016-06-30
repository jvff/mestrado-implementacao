#ifndef MORPHOLOGICAL_GRADIENT_FILTER_TEST_DATA_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_TEST_DATA_HPP

#include "Image.hpp"
#include "MorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractMorphologicalGradientTestData.hpp"

#include "../ChainableMethodMacros.hpp"

template <typename PixelType,
        typename DestinationImageType = SimpleArrayImage<PixelType>,
        typename SourceImageType = Image<PixelType> >
class MorphologicalGradientFilterTestData
        : public AbstractMorphologicalGradientTestData<
                MorphologicalGradientFilter<SourceImageType,
                        DestinationImageType>,
                PixelType, DestinationImageType> {
private:
    using FilterType = MorphologicalGradientFilter<SourceImageType,
            DestinationImageType>;
    using SuperClass = AbstractMorphologicalGradientTestData<FilterType,
            PixelType, DestinationImageType>;
    using ThisType = MorphologicalGradientFilterTestData<PixelType,
            DestinationImageType, SourceImageType>;

public:
    ~MorphologicalGradientFilterTestData() {
        this->tryToRunTest();
    }

    CHAIN(setStructureSize, unsigned int size) {
        if (SuperClass::setStructureSize(size))
            this->initializeFilter(size);
    }

    CHAIN_PARENT_METHOD(setDimensions)
    CHAIN_PARENT_METHOD(setBackground)
    CHAIN_PARENT_METHOD(drawSquare)
};

#endif
