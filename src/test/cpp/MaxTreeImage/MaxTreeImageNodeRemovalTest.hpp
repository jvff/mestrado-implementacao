#ifndef MAX_TREE_IMAGE_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_IMAGE_NODE_REMOVAL_TEST_HPP

#include <functional>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImage.hpp"

#include "../DummyTypes.hpp"
#include "MaxTreeImageTest.hpp"

class MaxTreeImageNodeRemovalTest
        : public MaxTreeImageTest<std::less<DummyType> > {
};

#endif
