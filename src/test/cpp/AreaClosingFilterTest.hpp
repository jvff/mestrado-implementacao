#ifndef AREA_CLOSING_FILTER_TEST_HPP
#define AREA_CLOSING_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "AreaClosingTestData.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = AreaClosingTestData<PixelType, ImageType>;

#endif
