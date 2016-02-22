#ifndef BEST_NEIGHBOR_TEST_HPP
#define BEST_NEIGHBOR_TEST_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "PixelNeighborhood.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"

#include "ImageMaskHelper.hpp"

struct PixelNeighborhoodBestNeighborTestParameter {
    SimpleArrayImage<bool> maskImage;
    SimpleArrayImage<DummyType> sourceImage;
    SimpleArrayImage<Pixel<DummyType> > expectedBestNeighbors;
    std::function<bool(const Pixel<DummyType>&, const Pixel<DummyType>&)>
            comparator;
};

using TestParameter = PixelNeighborhoodBestNeighborTestParameter;

class PixelNeighborhoodBestNeighborTest
        : public ::testing::TestWithParam<TestParameter> {
protected:
    static constexpr unsigned int width = 3u;
    static constexpr unsigned int height = 3u;

    using Comparator = std::function<bool(const Pixel<DummyType>&,
            const Pixel<DummyType>&)>;

public:
    static std::vector<TestParameter> generateParameters() {
        auto imageMasks = createImageMasks();

        auto firstTestImage = createFirstTestImage();
        auto secondTestImage = createSecondTestImage();

        auto firstComparator = std::less<Pixel<DummyType> >();
        auto secondComparator = std::greater<Pixel<DummyType> >();

        std::vector<TestParameter> parameters;

        for (auto& imageMask : imageMasks) {
            auto firstParameter = createTestParameter(imageMask,
                    firstTestImage, firstComparator);
            auto secondParameter = createTestParameter(imageMask,
                    firstTestImage, secondComparator);
            auto thirdParameter = createTestParameter(imageMask,
                    secondTestImage, secondComparator);
            auto fourthParameter = createTestParameter(imageMask,
                    secondTestImage, secondComparator);

            parameters.push_back(firstParameter);
            parameters.push_back(secondParameter);
            parameters.push_back(thirdParameter);
            parameters.push_back(fourthParameter);
        }

        return parameters;
    }

private:
    static SimpleArrayImage<DummyType> createFirstTestImage() {
        SimpleArrayImage<DummyType> image(width, height);

        image = [=] (unsigned int x, unsigned int y) -> DummyType {
            return DummyType{ (int)(x + y * width) };
        };

        return image;
    }

    static SimpleArrayImage<DummyType> createSecondTestImage() {
        SimpleArrayImage<DummyType> image(width, height);

        image.setPixel(1, 1, DummyType{ 0 });
        image.setPixel(1, 2, DummyType{ 1 });
        image.setPixel(0, 2, DummyType{ 2 });
        image.setPixel(0, 1, DummyType{ 3 });
        image.setPixel(0, 0, DummyType{ 4 });
        image.setPixel(1, 0, DummyType{ 5 });
        image.setPixel(2, 0, DummyType{ 6 });
        image.setPixel(2, 1, DummyType{ 7 });
        image.setPixel(2, 2, DummyType{ 8 });

        return image;
    }

    static std::vector<SimpleArrayImage<bool> > createImageMasks() {
        auto helper = ImageMaskHelper(width, height);
        auto masksWithAvailableNeighborForAllPixels =
                ImageMaskHelper::imageMaskHasAvailableNeighborForAllPixels;

        return helper.createImageMasks(masksWithAvailableNeighborForAllPixels);
    }

    static TestParameter createTestParameter(
            const SimpleArrayImage<bool>& imageMask,
            const SimpleArrayImage<DummyType>& sourceImage,
            Comparator comparator) {
        auto expectedResult = createExpectedResult(imageMask, sourceImage,
                comparator);

        return TestParameter{ imageMask, sourceImage, expectedResult,
                comparator };
    }

    static SimpleArrayImage<Pixel<DummyType> > createExpectedResult(
            const Image<bool>& imageMask, const Image<DummyType>& sourceImage,
            Comparator comparator) {
        const auto maxX = width - 1;
        const auto maxY = height - 1;

        SimpleArrayImage<Pixel<DummyType> > expectedResult(width, height);

        expectedResult = [&] (unsigned int x, unsigned int y)
                -> Pixel<DummyType> {
            auto expectedBestPixel = Pixel<DummyType>{ 0, 0, DummyType{ 0 } };
            auto firstWasSet = false;

            attemptToGetBestPixel(firstWasSet, expectedBestPixel, imageMask,
                    sourceImage, comparator, x > 0, x - 1, y);

            attemptToGetBestPixel(firstWasSet, expectedBestPixel, imageMask,
                    sourceImage, comparator, y > 0, x, y - 1);

            attemptToGetBestPixel(firstWasSet, expectedBestPixel, imageMask,
                    sourceImage, comparator, x < maxX, x + 1, y);

            attemptToGetBestPixel(firstWasSet, expectedBestPixel, imageMask,
                    sourceImage, comparator, y < maxY, x, y + 1);

            return expectedBestPixel;
        };

        return expectedResult;
    }

    static void attemptToGetBestPixel(bool& firstWasSet,
            Pixel<DummyType>& bestPixel, const Image<bool>& imageMask,
            const Image<DummyType>& sourceImage, Comparator comparator,
            bool coordinateIsValid, unsigned int x, unsigned int y) {
        if (coordinateIsValid && imageMask.getPixelValue(x, y) == false) {
            auto neighborPixel = sourceImage.getPixel(x, y);
            auto neighborIsBetter = comparator(bestPixel, neighborPixel);

            if (firstWasSet == false || neighborIsBetter) {
                bestPixel = neighborPixel;
                firstWasSet = true;
            }
        }
    }

protected:
    PixelNeighborhood<DummyType> neighborhood;
    SimpleArrayImage<bool> maskImage;
    SimpleArrayImage<DummyType> sourceImage;
    SimpleArrayImage<Pixel<DummyType> > expectedResult;
    Comparator comparator;
    const Image<bool>& maskImageReference;
    const Image<DummyType>& sourceImageReference;

public:
    PixelNeighborhoodBestNeighborTest() : maskImage(width, height),
            sourceImage(width, height), expectedResult(width, height),
            maskImageReference(maskImage), sourceImageReference(sourceImage) {
    }

    void SetUp() {
        auto testParameter = GetParam();

        maskImage = testParameter.maskImage;
        sourceImage = testParameter.sourceImage;
        expectedResult = testParameter.expectedBestNeighbors;
        comparator = testParameter.comparator;
    }
};

#define TEST_C(testName) \
    TEST_P(PixelNeighborhoodBestNeighborTest, testName)

#endif
