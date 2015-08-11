#ifndef MORPHOLOGICAL_GRADIENT_FILTER_TEST_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "ChainableMethodMacros.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class MorphologicalGradientFilterTestData : public AbstractFilterTestData<
        MorphologicalGradientFilter<PixelType, PixelType, ImageType>,
        PixelType, PixelType, ImageType, ImageType> {
private:
    using FilterType = MorphologicalGradientFilter<PixelType, PixelType,
            ImageType>;
    using SuperClass = AbstractFilterTestData<FilterType, PixelType, PixelType,
            ImageType, ImageType>;
    using State = AbstractTestData::State;
    using ThisType = MorphologicalGradientFilterTestData<PixelType, ImageType>;

    unsigned int structureSize;

public:
    ~MorphologicalGradientFilterTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height))
            this->state = State::SETTING_UP;
    }

    CHAIN(setStructureSize, unsigned int size) {
        if (this->stateIs(State::SETTING_UP)) {
            structureSize = size;

            this->initializeFilter(size);
        }
    }

    CHAIN(setBackground, const PixelType& color) {
        if (stateIs(State::SETTING_UP)) {
            auto fillImage = [=] (unsigned int, unsigned int) -> PixelType {
                return color;
            };

            *this->sourceImage = fillImage;
            *this->expectedImage = fillImage;

            this->state = State::READY;
        }
    }

    CHAIN(drawSquare, unsigned int x, unsigned int y, unsigned int size,
            const PixelType& color) {
        if (stateIs(State::READY)) {
            Square square(x, y, size);
            Border border(x, y, size, structureSize);

            *this->sourceImage = [&] (unsigned int x, unsigned y) -> PixelType {
                if (square.contains(x, y))
                    return color;
                else
                    return this->sourceImage->getPixel(x, y);
            };

            *this->expectedImage = [&] (unsigned int x, unsigned int y)
                    -> PixelType {
                if (border.contains(x, y))
                    return color;
                else
                    return this->expectedImage->getPixel(x, y);
            };
        }
    }

private:
    using SuperClass::stateIs;

    void finishSetUp() override {
        this->state = State::CANCELLED;
    }

private:
    struct Square {
        bool isValid;
        unsigned int startX;
        unsigned int startY;
        unsigned int endX;
        unsigned int endY;

        Square(unsigned int x, unsigned int y, unsigned int size) {
            isValid = size > 0;
            startX = x;
            startY = y;
            endX = x + size - 1;
            endY = y + size - 1;
        }

        bool contains(unsigned int x, unsigned int y) const {
            return isValid && isBetween(x, startX, endX)
                && isBetween(y, startY, endY);
        }

        bool isBetween(unsigned int value, unsigned int start,
                unsigned int end) const {
            return value >= start && value <= end;
        }
    };

    struct Border {
        std::unique_ptr<Square> outer;
        std::unique_ptr<Square> inner;

        Border(unsigned int x, unsigned int y, unsigned int size,
                unsigned int thickness) {
            int unrestrictedOuterX = (int)x - (int)thickness;
            int unrestrictedOuterY = (int)y - (int)thickness;
            int unrestrictedInnerSize = (int)size - 2 * (int)thickness;

            auto outerX = (unsigned int)std::max(0, unrestrictedOuterX);
            auto outerY = (unsigned int)std::max(0, unrestrictedOuterY);
            auto innerX = x + thickness;
            auto innerY = y + thickness;

            auto outerSize = size + 2 * thickness;
            auto innerSize = (unsigned int)std::max(0, unrestrictedInnerSize);

            outer.reset(new Square(outerX, outerY, outerSize));
            inner.reset(new Square(innerX, innerY, innerSize));
        }

        bool contains(unsigned int x, unsigned int y) const {
            return outer->contains(x, y) && !inner->contains(x, y);
        }
    };
};

#endif
