#ifndef AREA_CLOSING_FILTER_TEST_HPP
#define AREA_CLOSING_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AbstractFilterTestData.hpp"
#include "AreaClosingTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
class AbstractAreaClosingFilterTestData : public AbstractFilterTestData<
        AreaClosingFilter<ImageType, ImageType>, ImageType, ImageType> {
private:
    using FilterType = AreaClosingFilter<ImageType, ImageType>;
    using SuperClass = AbstractFilterTestData<FilterType, ImageType, ImageType>;

protected:
    void runTest() override {
        this->initializeFilter(getMaximumHoleSize());

        SuperClass::runTest();
    }

    virtual unsigned int getMaximumHoleSize() const = 0;
};

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaClosingTestData<
        AbstractAreaClosingFilterTestData<PixelType, ImageType>,
        PixelType, ImageType>;

#endif
