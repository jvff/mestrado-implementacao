#ifndef BOOL_IMAGE_TEST_HPP
#define BOOL_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "ImageImplementationTest.hpp"

template <typename ImageType>
class BoolImageTest : public ImageImplementationTest<ImageType, bool> {
};

#endif
