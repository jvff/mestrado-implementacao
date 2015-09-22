#ifndef AREA_OPENING_FILTER_TEST_HPP
#define AREA_OPENING_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "AreaOpeningTestData.hpp"
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
        this->initializeFilter(getMaximumPeakSize());

        SuperClass::runTest();
    }

    virtual unsigned int getMaximumPeakSize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaOpeningTestData<
        AbstractAreaOpeningFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
