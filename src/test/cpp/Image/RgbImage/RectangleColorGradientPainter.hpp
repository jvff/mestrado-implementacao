#ifndef RECTANGLE_COLOR_GRADIENT_PAINTER_HPP
#define RECTANGLE_COLOR_GRADIENT_PAINTER_HPP

#include <cmath>
#include <memory>

#include "Coordinate.hpp"

#include "ColorChannel.hpp"

template <typename PixelType>
class RectangleColorGradientPainter {
private:
    using ColorChannelPointer = std::shared_ptr<ColorChannel<PixelType> >;

private:
    unsigned int width;
    unsigned int height;
    bool withAlpha;

    float alphaConversionFactor;
    float redConversionFactor;
    float greenAndBlueConversionFactor;

    ColorChannelPointer redChannel;
    ColorChannelPointer greenChannel;
    ColorChannelPointer blueChannel;
    ColorChannelPointer alphaChannel;

    Coordinate topLeftCorner;
    Coordinate topRightCorner;
    Coordinate bottomLeftCorner;
    Coordinate bottomRightCorner;

public:
    RectangleColorGradientPainter(unsigned int width, unsigned int height,
            bool withAlpha)
            : width(width), height(height), withAlpha(withAlpha) {
        initializeCoordinates();
        calculateConversionFactors();
        calculateChannelParameters();
    }

    PixelType operator() (unsigned int x, unsigned int y) const {
        auto redComponent = getRedComponent(x, y);
        auto greenComponent = getGreenComponent(x, y);
        auto blueComponent = getBlueComponent(x, y);
        auto alphaComponent = getAlphaComponent(x, y);

        return makePixelValue(redComponent, greenComponent, blueComponent,
                alphaComponent);
    }

    float getRedComponent(unsigned int x, unsigned int y) const {
        return calculateComponent(x, y, topRightCorner, redConversionFactor);
    }

    float getGreenComponent(unsigned int x, unsigned int y) const {
        return calculateComponent(x, y, bottomLeftCorner,
                greenAndBlueConversionFactor);
    }

    float getBlueComponent(unsigned int x, unsigned int y) const {
        return calculateComponent(x, y, bottomRightCorner,
                greenAndBlueConversionFactor);
    }

    float getAlphaComponent(unsigned int x, unsigned int y) const {
        return calculateComponent(x, y, topLeftCorner, alphaConversionFactor);
    }

    const ColorChannel<PixelType>& getRedChannel() {
        return *redChannel;
    }

    const ColorChannel<PixelType>& getGreenChannel() {
        return *greenChannel;
    }

    const ColorChannel<PixelType>& getBlueChannel() {
        return *blueChannel;
    }

    const ColorChannel<PixelType>& getAlphaChannel() {
        return *alphaChannel;
    }

private:
    void initializeCoordinates() {
        topLeftCorner = Coordinate(0, 0);
        topRightCorner = Coordinate(width - 1, 0),
        bottomLeftCorner = Coordinate(0, height - 1);
        bottomRightCorner = Coordinate(width - 1, height - 1);
    }

    void calculateConversionFactors() {
        auto farthestPointForRedChannel = Coordinate(width / 2, height - 1);
        auto farthestPointForGreenChannel = Coordinate(width - 1, height / 2);
        auto farthestPointForAlphaChannel = bottomRightCorner;

        alphaConversionFactor = calculateConversionFactor(
                farthestPointForAlphaChannel);

        redConversionFactor = calculateConversionFactor(
                farthestPointForRedChannel);

        greenAndBlueConversionFactor = calculateConversionFactor(
                farthestPointForGreenChannel);
    }

    float calculateConversionFactor(const Coordinate& farthestPoint) {
        auto maximumDistance = topLeftCorner.distanceTo(farthestPoint);

        return 1.f / maximumDistance;
    }

    void calculateChannelParameters() {
        unsigned int numChannels = withAlpha ? 4 : 3;

        redChannel.reset(new ColorChannel<PixelType>(numChannels, false));
        greenChannel.reset(new ColorChannel<PixelType>(numChannels, true));
        blueChannel.reset(new ColorChannel<PixelType>(numChannels, false));

        if (withAlpha) {
            alphaChannel.reset(new ColorChannel<PixelType>(numChannels, false));
            blueChannel->isAfter(*alphaChannel);
        } else
            alphaChannel.reset(new ColorChannel<PixelType>(0, false));

        greenChannel->isAfter(*blueChannel);
        redChannel->isAfter(*greenChannel);
    }

    float calculateComponent(unsigned int x, unsigned int y,
            const Coordinate& referenceCorner, float conversionFactor) const {
        auto coordinate = Coordinate(x, y);
        auto distanceToTopLeftCorner = coordinate.distanceTo(topLeftCorner);
        auto distanceToReferenceCorner = coordinate.distanceTo(referenceCorner);

        auto distanceToNearestCorner = std::min(distanceToTopLeftCorner,
                distanceToReferenceCorner);

        return 1.f - distanceToNearestCorner * conversionFactor;
    }

    PixelType makePixelValue(float redComponent, float greenComponent,
            float blueComponent, float alphaComponent) const {
        PixelType pixel = 0;

        redChannel->apply(std::abs(redComponent), pixel);
        greenChannel->apply(std::abs(greenComponent), pixel);
        blueChannel->apply(std::abs(blueComponent), pixel);
        alphaChannel->apply(std::abs(alphaComponent), pixel);

        return pixel;
    }
};

#endif
