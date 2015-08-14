#ifndef ABSTRACT_MORPHOLOGICAL_GRADIENT_TEST_DATA_HPP
#define ABSTRACT_MORPHOLOGICAL_GRADIENT_TEST_DATA_HPP

#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"

template <typename FilterType, typename PixelType,
        typename ImageType = SimpleArrayImage<PixelType> >
class AbstractMorphologicalGradientTestData : public AbstractFilterTestData<
        FilterType, PixelType, PixelType, ImageType, ImageType> {
private:
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterTestData<FilterType, PixelType, PixelType,
            ImageType, ImageType>;
    using ThisType = AbstractMorphologicalGradientTestData<FilterType,
            PixelType, ImageType>;

protected:
    unsigned int structureSize;

public:
    void setDimensions(unsigned int width, unsigned int height) {
        if (SuperClass::setDimensions(width, height)) {
            *this->expectedImage = [] (unsigned int, unsigned int)
                    -> PixelType {
                return 0;
            };

            this->state = State::SETTING_UP;
        }
    }

    bool setStructureSize(unsigned int size) {
        if (this->stateIs(State::SETTING_UP)) {
            structureSize = size;

            return true;
        } else
            return false;
    }

    void setBackground(const PixelType& color) {
        if (stateIs(State::SETTING_UP)) {
            *this->sourceImage = [=] (unsigned int, unsigned int) -> PixelType {
                return color;
            };

            this->state = State::READY;
        }
    }

    void drawSquare(unsigned int x, unsigned int y, unsigned int size,
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
                    return color - getErodedPixel(x, y);
                else if (border.surrounds(x, y))
                    return 0;
                else
                    return this->expectedImage->getPixel(x, y);
            };
        }
    }

protected:
    using SuperClass::stateIs;

private:
    void finishSetUp() override {
        this->state = State::CANCELLED;
    }

    PixelType getErodedPixel(unsigned int x, unsigned int y) {
        auto pixel = this->sourceImage->getPixel(x, y);
        auto maxX = this->sourceImage->getWidth() - 1;
        auto maxY = this->sourceImage->getHeight() - 1;

        auto startU = structureSize >= x ? 0 : x - structureSize;
        auto startV = structureSize >= y ? 0 : y - structureSize;
        auto endU = std::min(maxX, x + structureSize);
        auto endV = std::min(maxY, y + structureSize);

        for (unsigned int u = startU; u <= endU; ++u) {
            for (unsigned int v = startV; v <= endV; ++v)
                pixel = std::min(pixel, this->sourceImage->getPixel(u, v));
        }

        return pixel;
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

        bool surrounds(unsigned int x, unsigned int y) const {
            return inner->contains(x, y);
        }
    };
};

#endif
