#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP

#include <memory>
#include <set>
#include <vector>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeImageFilterImplementation.hpp"
#include "MinMaxTreeNode.hpp"

#include "DummyTypes.hpp"
#include "FakeMinMaxTreeImageFilterImplementation.hpp"
#include "NodeVerificationHelper.hpp"
#include "SimpleArrayImage.hpp"

class MinMaxTreeImageFilterImplementationTest : public ::testing::Test,
        protected NodeVerificationHelper<DummyType, std::greater<DummyType> > {
protected:
    using PixelType = DummyType;
    using LevelOrderComparator = std::greater<PixelType>;
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using NodePointer = std::shared_ptr<NodeType>;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using ImageType = MinMaxTreeImage<InternalImageType, LevelOrderComparator>;
    using ImplementationType = MinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
    using FakeImplementationType = FakeMinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;

protected:
    std::shared_ptr<ImageType> sourceImage;
    std::shared_ptr<ImageType> destinationImage;
    std::shared_ptr<FakeImplementationType> implementation;

protected:
    MinMaxTreeImageFilterImplementationTest() {
        initialize(1, 1);
    }

    void initialize(unsigned int width, unsigned int height) {
        sourceImage = std::make_shared<ImageType>(width, height);
        destinationImage = std::make_shared<ImageType>(width, height);

        implementation = std::make_shared<FakeImplementationType>(*sourceImage,
                *destinationImage);
    }

    template <typename... RemainingParameterTypes>
    void verifyNodeSet(const std::set<NodeType>& nodeSet,
            const RemainingParameterTypes&... remainingParameters) {
        auto firstPosition = nodeSet.begin();
        auto lastPosition = nodeSet.end();

        verifyNodesInSet(firstPosition, lastPosition, remainingParameters...);
    }

    void verifyNodesInSet(std::set<NodeType>::const_iterator& positionInSet,
            const std::set<NodeType>::const_iterator& lastPosition) {
        assertThat(positionInSet).isEqualTo(lastPosition);
    }

    template <typename... RemainingParameterTypes>
    void verifyNodesInSet(std::set<NodeType>::const_iterator& positionInSet,
            const std::set<NodeType>::const_iterator& lastPosition,
            const NodePointer& expectedNodePointer,
            const RemainingParameterTypes&... remainingParameters) {
        assertThat(positionInSet).isNotEqualTo(lastPosition);

        verifySingleNodeInSet(positionInSet, expectedNodePointer);

        positionInSet++;

        verifyNodesInSet(positionInSet, lastPosition, remainingParameters...);
    }

    template <typename... RemainingParameterTypes>
    void verifyNodesInSet(std::set<NodeType>::const_iterator& positionInSet,
            const std::set<NodeType>::const_iterator& lastPosition,
            const PixelType& nodeLevel, unsigned int nodeId,
            const RemainingParameterTypes&... remainingParameters) {
        assertThat(positionInSet).isNotEqualTo(lastPosition);

        verifySingleNodeInSet(positionInSet, nodeLevel, nodeId);

        positionInSet++;

        verifyNodesInSet(positionInSet, lastPosition, remainingParameters...);
    }

    void verifySingleNodeInSet(std::set<NodeType>::const_iterator& position,
            const PixelType& nodeLevel, unsigned int nodeId) {
        auto& node = *position;

        verifyNodeData(node, nodeLevel, nodeId);
    }

    void verifySingleNodeInSet(std::set<NodeType>::const_iterator& position,
            const NodePointer& nodePointer) {
        auto& node = *position;

        verifyNode(node, nodePointer);
    }
};

#endif
