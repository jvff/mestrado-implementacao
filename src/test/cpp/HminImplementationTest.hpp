#ifndef HMIN_IMPLEMENTATION_TEST_HPP
#define HMIN_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "PaintableTestData.hpp"

class HminImplementationTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = HminImplementation<SourceImageType,
            DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class HminImplementationTestData : public PaintableTestData<
        AbstractFilterImplementationTestData<
                HminImplementation<ImageType, ImageType>, ImageType, ImageType>,
        ImageType, ImageType> {
private:
    using ImplementationType = HminImplementation<ImageType, ImageType>;
    using State = AbstractTestData::State;
    using ParentTestDataType = AbstractFilterImplementationTestData<
            ImplementationType, ImageType, ImageType>;
    using SuperClass = PaintableTestData<ParentTestDataType, ImageType,
            ImageType>;
    using ThisType = HminImplementationTestData<PixelType, ImageType>;

    PixelType featureHeight;

public:
    virtual ~HminImplementationTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            this->state = State::SETTING_UP;
    }

    CHAIN(setFeatureHeight, const PixelType& featureHeight) {
        if (stateIs(State::SETTING_UP)) {
            this->featureHeight = featureHeight;

            this->state = State::READY;
        }
    }

    CHAIN_PARENT_METHOD(setBackground)
    CHAIN_PARENT_METHOD(setExpectedBackground)

    CHAIN_PARENT_METHOD(drawSquare)
    CHAIN_PARENT_METHOD(drawExpectedSquare)

protected:
    using SuperClass::stateIs;

    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        return ImplementationType(featureHeight, sourceImage, destinationImage);
    }
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = HminImplementationTestData<PixelType, ImageType>;

#endif
