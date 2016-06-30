#ifndef MORPHOLOGICAL_GRADIENT_FILTER_TEST_DATA_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_TEST_DATA_HPP

#include "MorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractMorphologicalGradientTestData.hpp"

#include "../ChainableMethodMacros.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class MorphologicalGradientFilterTestData
        : public AbstractMorphologicalGradientTestData<
                MorphologicalGradientFilter<Image<PixelType>, ImageType>,
                PixelType, ImageType> {
private:
    using FilterType = MorphologicalGradientFilter<Image<PixelType>, ImageType>;
    using SuperClass = AbstractMorphologicalGradientTestData<FilterType,
            PixelType, ImageType>;
    using ThisType = MorphologicalGradientFilterTestData<PixelType, ImageType>;

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
