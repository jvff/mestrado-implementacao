#ifndef NEIGHBOR_AVAILABILITY_TEST_HPP
#define NEIGHBOR_AVAILABILITY_TEST_HPP

#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "PixelNeighborhood.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"

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
        const auto numberOfBoards = createMask(width * height);

        std::vector<TestParameter> parameters;

        for (auto boardId = 0u; boardId < numberOfBoards; ++boardId) {
            auto board = createBoard(boardId);
            auto expectedResult = createExpectedResultMask(board);
            auto testParameter = TestParameter{ board, expectedResult };

            parameters.push_back(testParameter);
        }

        return parameters;
    }

private:
    static SimpleArrayImage<bool> createBoard(unsigned int boardId) {
        auto board = SimpleArrayImage<bool>(width, height);

        board = [=] (unsigned int x, unsigned int y) -> bool {
            auto coordinateBit = x + y * width;

            return bitIsSet(coordinateBit, boardId);
        };

        return board;
    }

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

    static constexpr unsigned int createMask(unsigned int bits) {
        return (1u << bits) - 1;
    }

    static constexpr unsigned int createMaskForBit(unsigned int bit) {
        return 1u << bit;
    }

    static bool bitIsSet(unsigned int bit, unsigned int bits) {
        auto bitMask = createMaskForBit(bit);

        return (bits & bitMask) != 0;
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
