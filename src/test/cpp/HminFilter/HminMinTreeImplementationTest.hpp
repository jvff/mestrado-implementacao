#ifndef HMIN_MIN_TREE_IMPLEMENTATION_TEST_HPP
#define HMIN_MIN_TREE_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminMinTreeImplementation.hpp"
#include "MinTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

class HminMinTreeImplementationTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using ImageType = MinTreeImage<InternalImageType>;
    using DummyImplementation = HminMinTreeImplementation<InternalImageType>;
};

#endif
