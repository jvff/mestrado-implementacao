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

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    void assignPixelToLatestNode(unsigned int x, unsigned int y) {
        auto level = getPixelValue(x, y);
        auto& latestNode = getLatestNodeAtLevel(level);

        nodeIdImage.setPixel(x, y, latestNode->id);
    }

    const NodeType& getNodeOfPixel(unsigned int x, unsigned int y) {
        auto level = internalImage.getPixelValue(x, y);
        auto nodeId = nodeIdImage.getPixelValue(x, y);
        auto& nodePointer = getNode(level, nodeId);

        return *nodePointer;
    }

private:
    NodePointerType& getNode(PixelType level, unsigned int nodeId) {
        auto& nodesAtLevel = getNodesAtLevel(level);

        return nodesAtLevel[nodeId];
    }

    NodePointerType& getLatestNodeAtLevel(PixelType level) {
        auto& nodesAtLevel = getNodesAtLevel(level);

        return nodesAtLevel.back();
    }

    NodeList& getNodesAtLevel(PixelType level) {
        if (treeDoesNotHaveLevel(level))
            createNewLevel(level);

        return treeLevels[level];
    }

    bool treeDoesNotHaveLevel(PixelType level) {
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

    NodePointerType& getLatestNodeAtLevelBefore(PixelType level) {
        if (treeLevels.empty() || level == getFirstLevel())
            return noParent;

        auto previousLevel = getLevelBefore(level);

        return getLatestNodeAtLevel(previousLevel);
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

#endif
