#ifndef HMAX_FILTER_TEST_HPP
#define HMAX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "HmaxFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "PaintableTestData.hpp"
#include "RectanglePainter.hpp"

class HmaxFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HmaxFilter<SourceImageType, DestinationImageType>;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class HmaxFilterTestData : public PaintableTestData<
        AbstractFilterTestData<HmaxFilter<ImageType, ImageType>, ImageType,
                ImageType>,
        ImageType, ImageType> {
private:
    using FilterType = HmaxFilter<ImageType, ImageType>;
    using State = AbstractTestData::State;
    using ParentTestDataType = AbstractFilterTestData<FilterType, ImageType,
            ImageType>;
    using SuperClass = PaintableTestData<ParentTestDataType, ImageType,
            ImageType>;
    using ThisType = HmaxFilterTestData<PixelType, ImageType>;

public:
    virtual ~HmaxFilterTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            this->state = State::SETTING_UP;
    }

    CHAIN(setFeatureHeight, const PixelType& featureHeight) {
        if (stateIs(State::SETTING_UP)) {
            this->initializeFilter(featureHeight);

            this->state = State::READY;
        }
    }

    CHAIN_PARENT_METHOD(setBackground)
    CHAIN_PARENT_METHOD(setExpectedBackground)

    CHAIN_PARENT_METHOD(drawSquare)
    CHAIN_PARENT_METHOD(drawExpectedSquare)

protected:
    using SuperClass::stateIs;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = HmaxFilterTestData<PixelType, ImageType>;

#endif
