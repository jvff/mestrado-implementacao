#ifndef MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_FILTER_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class TestData {
private:
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using Pixel = std::tuple<unsigned int, unsigned int, const PixelType&>;

public:
    FilterType filter;
    ImageType sourceImage;
    ImageType markerImage;
    ImageType expectedImage;

public:
    TestData(unsigned int width, unsigned int height)
            : sourceImage(width, height), markerImage(width, height),
            expectedImage(width, height) {
    }

    void setMarker(PixelType background, const Pixel& pixel) {
        markerImage = [background] (unsigned int, unsigned int) -> PixelType {
            return background;
        };

        unsigned int x;
        unsigned int y;
        PixelType value;

        std::tie(x, y, value) = pixel;

        markerImage.setPixel(x, y, value);
    }

    void applyFilterAndVerifyResult() {
        filter.apply(sourceImage, markerImage);

        assertThat(markerImage).isEqualTo(expectedImage);
    }
};

#endif
