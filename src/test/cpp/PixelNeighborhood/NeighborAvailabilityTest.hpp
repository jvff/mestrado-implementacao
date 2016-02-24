#ifndef NEIGHBOR_AVAILABILITY_TEST_HPP
#define NEIGHBOR_AVAILABILITY_TEST_HPP

#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "PixelNeighborhood.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"

#include "ImageMaskHelper.hpp"

struct PixelNeighborhoodNeighborAvailabilityTestParameter {
    SimpleArrayImage<bool> maskImage;
    SimpleArrayImage<bool> expectedPixelsWithAvailableNeighbors;
};

using TestParameter = PixelNeighborhoodNeighborAvailabilityTestParameter;

class PixelNeighborhoodNeighborAvailabilityTest
        : public ::testing::TestWithParam<TestParameter> {
protected:
    static constexpr unsigned int width = 3u;
    static constexpr unsigned int height = 3u;

public:
    static std::vector<TestParameter> generateParameters() {
        std::vector<TestParameter> parameters;

        auto helper = ImageMaskHelper(width, height);
        auto imageMasks = helper.createImageMasks();

        for (auto& imageMask : imageMasks) {
            auto expectedResult = createExpectedResultMask(imageMask);
            auto testParameter = TestParameter{ imageMask, expectedResult };

            parameters.push_back(testParameter);
        }

        return parameters;
    }

private:
    static SimpleArrayImage<bool> createExpectedResultMask(
            const Image<bool>& board) {
        const auto maxX = width - 1;
        const auto maxY = height - 1;
        auto resultMask = SimpleArrayImage<bool>(width, height);

        resultMask = [=, &board] (unsigned int x, unsigned int y) -> bool {
            auto shouldHaveAvailableNeighbor = false;

            if (x > 0)
                shouldHaveAvailableNeighbor |= !board.getPixelValue(x - 1, y);

            if (y > 0)
                shouldHaveAvailableNeighbor |= !board.getPixelValue(x, y - 1);

            if (x < maxX)
                shouldHaveAvailableNeighbor |= !board.getPixelValue(x + 1, y);

            if (y < maxY)
                shouldHaveAvailableNeighbor |= !board.getPixelValue(x, y + 1);

            return shouldHaveAvailableNeighbor;
        };

        return resultMask;
    }

protected:
    PixelNeighborhood<DummyType> neighborhood;
    SimpleArrayImage<bool> maskImage;
    SimpleArrayImage<bool> expectedResult;
    const Image<bool>& maskImageReference;

public:
    PixelNeighborhoodNeighborAvailabilityTest() : maskImage(width, height),
            expectedResult(width, height), maskImageReference(maskImage) {
    }

    void SetUp() override {
        auto testParameter = GetParam();

        maskImage = testParameter.maskImage;
        expectedResult = testParameter.expectedPixelsWithAvailableNeighbors;
    }
};

#define TEST_C(testName) \
    TEST_P(PixelNeighborhoodNeighborAvailabilityTest, testName)

#endif
