#ifndef MAX_TREE_IMAGE_TEST_HPP
#define MAX_TREE_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MaxTreeImageTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;
};

#endif
