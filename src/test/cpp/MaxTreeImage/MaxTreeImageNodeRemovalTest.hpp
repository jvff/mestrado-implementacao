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
protected:
    void verifyFilledImagePixels(Image<PixelType>& image, PixelType color) {
        auto width = image.getWidth();
        auto height = image.getHeight();

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                assertThat(image.getPixelValue(x, y)).isEqualTo(color);
        }
    }

    template <typename... RemainingParameterTypes>
    void verifyNode(const TreeNodeType& node, PixelType level, unsigned int id,
            const RemainingParameterTypes&... remainingParameters) {
        verifyNodeData(node, level, id);
        verifyNodeIsNotRoot(node);

        verifyNode(node.getParent(), remainingParameters...);
    }

    void verifyNode(const TreeNodeType& node, PixelType level,
            unsigned int id) {
        verifyNodeData(node, level, id);
        verifyNodeIsRoot(node);
    }

    void verifyNodeData(const TreeNodeType& node, PixelType level,
            unsigned int id) {
        assertThat(node.getLevel()).isEqualTo(level);
        assertThat(node.getId()).isEqualTo(id);
    }

    void verifyNodeIsRoot(const TreeNodeType& node) {
        assertThat(node.hasParent()).isEqualTo(false);
    }

    void verifyNodeIsNotRoot(const TreeNodeType& node) {
        assertThat(node.hasParent()).isEqualTo(true);
    }
};

#endif
