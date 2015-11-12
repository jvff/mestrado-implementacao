#ifndef HMIN_TEST_DATA_HPP
#define HMIN_TEST_DATA_HPP

#include "SimpleArrayImage.hpp"

#include "AbstractTestData.hpp"
#include "PaintableTestData.hpp"

template <typename ParentTestDataType, typename PixelType,
        typename ImageType = SimpleArrayImage<PixelType> >
class HminTestData : public PaintableTestData<ParentTestDataType, ImageType,
        ImageType> {
private:
    using State = AbstractTestData::State;
    using SuperClass = PaintableTestData<ParentTestDataType, ImageType,
            ImageType>;
    using ThisType = HminTestData<ParentTestDataType, PixelType, ImageType>;

    PixelType featureHeight;

public:
    virtual ~HminTestData() {
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

    PixelType getFeatureHeight() override {
        return featureHeight;
    }
};

#endif
