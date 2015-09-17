#ifndef WATERSHED_WAVE_IMAGE_TEST_HPP
#define WATERSHED_WAVE_IMAGE_TEST_HPP

#include <cmath>

#include "WatershedWaveExpectedImagePainter.hpp"

template <typename WatershedTestData>
class WatershedWaveImageTest {
private:
    using ThisClass = WatershedWaveImageTest<WatershedTestData>;
    using PaintFunction = std::function<unsigned char(unsigned int,
            unsigned int)>;
    using PaintMethod = std::function<unsigned char(ThisClass*, unsigned int,
            unsigned int)>;

    static const unsigned char separatorValue = 0;

    const unsigned int size;
    const unsigned int halfPeriods;

    WatershedTestData test;

    WatershedWaveExpectedImagePainter expectedImagePainter;

public:
    WatershedWaveImageTest() : size(40), halfPeriods(4),
            expectedImagePainter(size, halfPeriods) {
        test.setDimensions(size + 1, size + 1);
        *test.sourceImage = getPaintMethod(&ThisClass::drawSourceImage);
        *test.expectedImage = getPaintMethod(&ThisClass::drawExpectedImage);
    }

private:
    PaintFunction getPaintMethod(PaintMethod method) {
        return std::bind(method, this, std::placeholders::_1,
                std::placeholders::_2);
    }

    unsigned char drawSourceImage(unsigned int x, unsigned int y) {
        const double pi = 3.14159265358979323846;
        double factor = ((double)size) / ((double)halfPeriods);
        double u = x * pi / factor;
        double v = y * pi / factor;
        double value = std::sin(u) * std::sin(v);
        double height = (value + 1.0) * 255.0 / 2;

        return (unsigned char)height;
    }

    unsigned char drawExpectedImage(unsigned int x, unsigned int y) {
        return expectedImagePainter.getPixelValue(x, y);
    }
};

#endif
