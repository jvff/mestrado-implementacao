#ifndef LUMINANCE_FILTER_GRAYSCALE_IMAGE_IMPLEMENTATION_TEST_HPP
#define LUMINANCE_FILTER_GRAYSCALE_IMAGE_IMPLEMENTATION_TEST_HPP

#include "LuminanceFilterImplementationTests.hpp"

#include "../AbstractTestWithImage.hpp"

template <typename Aliases>
class LuminanceFilterGrayscaleImageImplementationTest
        : public AbstractTestWithImage<typename Aliases::RealSourceImageType> {
private:
    using RealSourceImageType = typename Aliases::RealSourceImageType;
    using SuperClass = AbstractTestWithImage<RealSourceImageType>;

protected:
    RealSourceImageType createSourceImage(unsigned int width,
            unsigned int height) {
        return SuperClass::createImage(width, height);
    }
};

#define TEST_C(testName) \
    TEST_C_FOR_TEST_CASE(LuminanceFilterGrayscaleImageImplementationTest, \
            testName, \
        using SuperClass::createSourceImage; \
    )

#endif
