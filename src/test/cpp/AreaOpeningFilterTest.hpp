#ifndef AREA_OPENING_FILTER_TEST_HPP
#define AREA_OPENING_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "AreaOpeningAndClosingTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaOpeningFilterTestData
        : public AbstractFilterTestData<AreaOpeningFilter<ImageType, ImageType>,
                ImageType, ImageType> {
private:
    using SuperClass = AbstractFilterTestData<
            AreaOpeningFilter<ImageType, ImageType>, ImageType, ImageType>;

protected:
    void runTest() override {
        this->initializeFilter(getMaximumExtremitySize());

        SuperClass::runTest();
    }

    virtual unsigned int getMaximumExtremitySize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningAndClosingTestData<
        AbstractAreaOpeningFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
