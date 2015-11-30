#ifndef MAX_TREE_IMAGE_HPP
#define MAX_TREE_IMAGE_HPP

#include <map>
#include <vector>

#include "Image.hpp"
#include "MaxTreeNode.hpp"
#include "SimpleArrayImage.hpp"

template <typename InternalImageType>
class MaxTreeImage : public Image<typename InternalImageType::PixelType> {
private:
    using PixelType = typename InternalImageType::PixelType;
    using NodeType = MaxTreeNode<PixelType>;
    using NodePointerType = std::shared_ptr<NodeType>;
    using NodeList = std::vector<NodePointerType>;
    using SuperClass = Image<PixelType>;

    InternalImageType internalImage;
    SimpleArrayImage<unsigned int> nodeIdImage;

    std::map<PixelType, NodeList> treeLevels;

    NodePointerType noParent;

public:
    MaxTreeImage(unsigned int width, unsigned int height)
            : SuperClass(width, height), internalImage(width, height),
            nodeIdImage(width, height) {
    }

    using SuperClass::operator=;

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    void assignPixelToLatestNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);
        auto& latestNode = getLatestNodeOrCreateFirstNodeAtLevel(level);

        nodeIdImage.setPixel(x, y, latestNode->id);
    }

    void assignPixelToNewNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);
        auto& newNode = createNodeAtLevel(level);

        nodeIdImage.setPixel(x, y, newNode->id);
    }

    const NodeType& getNodeOfPixel(unsigned int x, unsigned int y) const {
        auto level = internalImage.getPixelValue(x, y);
        auto nodeId = nodeIdImage.getPixelValue(x, y);
        auto& nodePointer = getNode(level, nodeId);

        return *nodePointer;
    }

private:
    const NodePointerType& getNode(PixelType level, unsigned int nodeId) const {
        auto& nodesAtLevel = getNodesAtLevel(level);

        return nodesAtLevel[nodeId];
    }

    NodePointerType& getLatestNodeOrCreateFirstNodeAtLevel(PixelType level) {
        auto& nodesAtLevel = getNodesAtLevelOrCreateLevel(level);

        return nodesAtLevel.back();
    }

    NodePointerType& createNodeAtLevel(PixelType level) {
        bool levelWasCreated = treeDoesNotHaveLevel(level);
        auto& nodesAtLevel = getNodesAtLevelOrCreateLevel(level);

        if (levelWasCreated)
            return nodesAtLevel.back();
        else
            return createNodeIn(level, nodesAtLevel);
    }

    const NodeList& getNodesAtLevel(PixelType level) const {
        if (treeDoesNotHaveLevel(level))
            throw std::string("Unavailable tree level");

        return treeLevels.at(level);
    }

    NodeList& getNodesAtLevelOrCreateLevel(PixelType level) {
        if (treeDoesNotHaveLevel(level))
            createNewLevel(level);

        return treeLevels[level];
    }

    bool treeDoesNotHaveLevel(PixelType level) const {
        auto notFound = treeLevels.end();

        return treeLevels.find(level) == notFound;
    }

    void createNewLevel(PixelType level) {
        NodeList nodesAtLevel;
        NodePointerType newNode(new NodeType);
        auto& parent = getLatestNodeAtLevelBefore(level);

        newNode->level = level;
        newNode->id = 0;
        newNode->parent = parent;

        nodesAtLevel.push_back(newNode);

        treeLevels[level] = nodesAtLevel;
    }

    NodePointerType& createNodeIn(PixelType level, NodeList& nodesAtLevel) {
        NodePointerType newNode(new NodeType);
        auto& parent = getLatestNodeAtLevelBefore(level);
        auto id = nodesAtLevel.size();

        newNode->level = level;
        newNode->id = id;
        newNode->parent = parent;

        nodesAtLevel.push_back(newNode);

        return nodesAtLevel[id];
    }

    NodePointerType& getLatestNodeAtLevelBefore(PixelType level) {
        if (treeLevels.empty() || level == getFirstLevel())
            return noParent;

        auto previousLevel = getLevelBefore(level);

        return getLatestNodeOrCreateFirstNodeAtLevel(previousLevel);
    }

    PixelType getFirstLevel() {
        auto firstLevelPosition = treeLevels.begin();
        auto firstLevelKeyValuePair = *firstLevelPosition;
        auto firstLevel = std::get<0>(firstLevelKeyValuePair);

        return firstLevel;
    }

    PixelType getLevelBefore(PixelType level) {
        auto position = treeLevels.find(level);

        --position;

        auto keyValuePair = *position;
        auto previousLevel = std::get<0>(keyValuePair);

        return previousLevel;
    }
};

template <typename InternalImageType>
static bool allNodesAreEqual(const MaxTreeImage<InternalImageType>& first,
        const MaxTreeImage<InternalImageType>& second) {
    auto width = first.getWidth();
    auto height = first.getHeight();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto firstNode = first.getNodeOfPixel(x, y);
            auto secondNode = second.getNodeOfPixel(x, y);

            if (firstNode.id != secondNode.id)
                return false;
        }
    }

    return true;
}

template <typename InternalImageType>
bool operator==(const MaxTreeImage<InternalImageType>& first,
        const MaxTreeImage<InternalImageType>& second) {
    return first.getWidth() == second.getWidth()
        && first.getHeight() == second.getHeight()
        && allPixelsAreEqual(first, second)
        && allNodesAreEqual(first, second);
}

#endif
