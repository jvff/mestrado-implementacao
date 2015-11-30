#ifndef MAX_TREE_TEST_DATA_HPP
#define MAX_TREE_TEST_DATA_HPP

#include "MaxTreeImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "PaintableTestData.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class MaxTreeTestData : public PaintableTestData<
        AbstractFilterImplementationTestData<
            MaxTreeImplementation<ImageType, ImageType>,
            ImageType, MaxTreeImage<ImageType> >,
        ImageType, MaxTreeImage<ImageType> > {
private:
    using ImplementationType = MaxTreeImplementation<ImageType, ImageType>;
    using DestinationImageType = MaxTreeImage<ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = PaintableTestData<
            AbstractFilterImplementationTestData<ImplementationType, ImageType,
                DestinationImageType>, ImageType, DestinationImageType>;
    using ThisType = MaxTreeTestData<PixelType, ImageType>;

    using SuperClass::state;
    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::expectedImage;

public:
    ~MaxTreeTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            state = State::READY;
    }

    CHAIN(setBackground, const PixelType& color) {
        SuperClass::setBackground(color);
        SuperClass::setExpectedBackground(color);

        initializeExpectedNodes();
    }

private:
    void initializeExpectedNodes() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                expectedImage->assignPixelToLatestNode(x, y);
        }
    }
};

#endif
