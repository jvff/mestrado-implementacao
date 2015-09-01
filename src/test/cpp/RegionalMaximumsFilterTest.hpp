#ifndef REGIONAL_MAXIMUMS_FILTER_TEST_HPP
#define REGIONAL_MAXIMUMS_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RegionalMaximumsFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class RegionalMaximumsFilterTestData : public AbstractFilterTestData<
        RegionalMaximumsFilter<Image<PixelType>, ImageType>, PixelType,
        PixelType, ImageType, ImageType> {
private:
    using FilterType = RegionalMaximumsFilter<Image<PixelType>, ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterTestData<FilterType, PixelType, PixelType,
            ImageType, ImageType>;
    using ThisType = RegionalMaximumsFilterTestData<PixelType, ImageType>;

public:
    RegionalMaximumsFilterTestData() {
        this->initializeFilter();
    }

    ~RegionalMaximumsFilterTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            *this->expectedImage = [] (unsigned int, unsigned int)
                    -> PixelType {
                return 0;
            };

            this->state = State::READY;
        }
    }

    CHAIN(setBackground, const PixelType& height) {
        if (stateIs(State::READY)) {
            *this->sourceImage = [&] (unsigned int, unsigned int)
                    -> PixelType {
                return height;
            };
        }
    }

    CHAIN(setPeak, unsigned int x, unsigned int y, const PixelType& height) {
        setRegionalMaximum(x, y, height);
    }

    CHAIN(drawPlateau, unsigned int x, unsigned int y, unsigned int width,
            unsigned int height, const PixelType& plateauHeight) {
        if (stateIs(State::READY) && width > 0 && height > 0) {
            auto startX = x;
            auto startY = y;
            auto endX = x + width - 1;
            auto endY = y + height - 1;

            for (x = startX; x <= endX; ++x) {
                for (y = startY; y <= endY; ++y)
                    setRegionalMaximum(x, y, plateauHeight);
            }
        }
    }

private:
    using SuperClass::stateIs;

    void finishSetUp() override {
        this->state = State::CANCELLED;
    }

    void setRegionalMaximum(unsigned int x, unsigned int y,
            const PixelType& height) {
        this->sourceImage->setPixel(x, y, height);
        this->expectedImage->setPixel(x, y, height);
    }
};

#endif
