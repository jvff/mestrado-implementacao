#ifndef INVERSION_TEST_DATA_HPP
#define INVERSION_TEST_DATA_HPP

#include "InversionImplementation.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterImplementationTestData.hpp"
#include "AbstractTestData.hpp"
#include "ChainableMethodMacros.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class InversionTestData : public AbstractFilterImplementationTestData<
        InversionImplementation<ImageType, ImageType>, ImageType, ImageType> {
private:
    using ImplementationType = InversionImplementation<ImageType, ImageType>;
    using State = AbstractTestData::State;
    using SuperClass = AbstractFilterImplementationTestData<ImplementationType,
            ImageType, ImageType>;
    using ThisType = InversionTestData<PixelType, ImageType>;

private:
    bool rangeWasSet;
    PixelType minimumValue;
    PixelType maximumValue;

    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::sourceImage;
    using SuperClass::expectedImage;

public:
    InversionTestData() : rangeWasSet(false) {
    }

    ~InversionTestData() {
        this->tryToRunTest();
    }

    CHAIN(setDimensions, unsigned int newWidth, unsigned int newHeight) {
        if (SuperClass::setDimensions(newWidth, newHeight))
            this->state = State::READY;
    }

    CHAIN(setRange, const PixelType& minimum, const PixelType& maximum) {
        if (stateIs(State::READY)) {
            minimumValue = minimum;
            maximumValue = maximum;
            rangeWasSet = true;
        }
    }

    CHAIN(setPixel, unsigned int x, unsigned int y, const PixelType& value) {
        if (stateIs(State::READY))
            sourceImage->setPixel(x, y, value);
    }

protected:
    void finishSetUp() override {
    }

    ImplementationType instantiateImplementation(const ImageType& sourceImage,
            ImageType& destinationImage) override {
        if (!rangeWasSet)
            discoverRange();

        prepareExpectedImage();

        if (rangeWasSet) {
            return ImplementationType(sourceImage, destinationImage,
                    minimumValue, maximumValue);
        } else
            return ImplementationType(sourceImage, destinationImage);
    }

private:
    using SuperClass::stateIs;

    void discoverRange() {
        minimumValue = sourceImage->getPixelValue(0, 0);
        maximumValue = minimumValue;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                auto pixel = sourceImage->getPixelValue(x, y);

                minimumValue = std::min(minimumValue, pixel);
                maximumValue = std::max(maximumValue, pixel);
            }
        }
    }

    void prepareExpectedImage() {
        *expectedImage = [=] (unsigned int x, unsigned int y) {
            auto pixelValue = sourceImage->getPixelValue(x, y);

            return maximumValue - pixelValue + minimumValue;
        };
    }
};

#endif
