#ifndef MAX_TREE_IMAGE_TEST_HPP
#define MAX_TREE_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

class MaxTreeImageTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;
};

#endif
