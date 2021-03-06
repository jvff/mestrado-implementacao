#ifndef OPEN_C_L_IMAGE_COMPARATOR_COMPARISON_TESTS_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_COMPARISON_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLImageComparator.hpp"

#include "../AbstractOpenCLTest.hpp"

class OpenCLImageComparatorComparisonTests : public AbstractOpenCLTest {
protected:
    using PixelType = unsigned int;
    using ImageType = OpenCLImage<PixelType>;
    using ComparatorType = OpenCLImageComparator<PixelType>;

protected:
    void paintImageWithUniquePixels(ImageType& image) {
        auto width = image.getWidth();

        image = [=] (unsigned int x, unsigned int y) -> PixelType {
            return x + y * width;
        };
    }
};

#define TEST_C(TestName) \
    TEST_F(OpenCLImageComparatorComparisonTests, TestName)

#endif
