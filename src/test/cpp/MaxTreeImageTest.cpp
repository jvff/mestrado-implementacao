#include "MaxTreeImageTest.hpp"

TEST_F(MaxTreeImageTest, classTemplateExists) {
    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}

TEST_F(MaxTreeImageTest, isImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMaxTreeImageType>::isSubClass(Of<ParentImageClass>());
}

TEST_F(MaxTreeImageTest, pixelTypeIsPubliclyAccessible) {
    using ImagePixelType = typename DummyMaxTreeImageType::PixelType;

    AssertThat<ImagePixelType>::isTheSame(As<PixelType>());
}

TEST_F(MaxTreeImageTest, isConstructible) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;

    AssertThat<DummyMaxTreeImageType>::isConstructible(With<WidthParameter,
            HeightParameter>());
}

TEST_F(MaxTreeImageTest, setsDimensions) {
    unsigned int width = 7539;
    unsigned int height = 401;

    DummyMaxTreeImageType image(width, height);

    assertThat(image.getWidth()).isEqualTo(width);
    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_F(MaxTreeImageTest, updatesInternalImage) {
    unsigned int width = 6;
    unsigned int height = 4;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);

    verifyPaintedImagePixels(image);
}

TEST_F(MaxTreeImageTest, allowsAssigningToRootNode) {
    unsigned int width = 3;
    unsigned int height = 2;
    PixelType rootNodeLevel = { 10 };

    DummyMaxTreeImageType image(width, height);

    fillImage(image, rootNodeLevel);
    assignPixelsToLatestNodes(image);

    auto expectedRootNode = makeNode(0u, rootNodeLevel);

    verifyNodes(image, expectedRootNode);
}

TEST_F(MaxTreeImageTest, nodeParentChain) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    verifyNodes(image, [&] (unsigned int x, unsigned int y)
            -> TreeNodeType {
        TreeNodePointer parent;
        int level = x + y * width;

        for (auto parentLevel = 0; parentLevel < level; ++parentLevel) {
            auto newParent = makeNode(0u, PixelType{ parentLevel }, parent);

            parent = newParent;
        }

        auto expectedNode = makeNode(0u, PixelType{ level }, parent);

        return *expectedNode;
    });
}

TEST_F(MaxTreeImageTest, forkingCreatesTreeBranch) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);
    auto background = PixelType{ 100 };
    auto foreground = PixelType{ 1000 };

    image.setPixel(0, 0, background);
    image.setPixel(1, 0, foreground);
    image.setPixel(0, 1, foreground);
    image.setPixel(1, 1, background);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 1);

    image.assignPixelToNewNode(1, 0);
    image.assignPixelToNewNode(0, 1);

    auto rootNode = makeNode(0u, background);

    verifyNodes(image, [=] (unsigned int x, unsigned int y) -> TreeNodeType {
        if (x == y)
            return *rootNode;
        else if (x == 1)
            return *makeNode(0u, foreground, rootNode);
        else
            return *makeNode(1u, foreground, rootNode);
    });
}

TEST_F(MaxTreeImageTest, imagesAreAssignableToLambdaFunction) {
    unsigned int width = 8;
    unsigned int height = 7;

    DummyMaxTreeImageType image(width, height);

    auto paintFunction = [width] (unsigned int x, unsigned int y) -> PixelType {
        return PixelType{ (int)(x + y * width * 2) };
    };

    image = paintFunction;

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto pixelValue = image.getPixelValue(x, y);
            auto expectedPixelValue = paintFunction(x, y);

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}

TEST_F(MaxTreeImageTest, separatedPartsOfRegionMayBeMislabeled) {
    DummyMaxTreeImageType image(3, 1);

    auto leftPixelColor = PixelType{ 14 };
    auto middlePixelColor = PixelType{ 16 };
    auto rightPixelColor = PixelType{ 15 };

    image.setPixel(0, 0, leftPixelColor);
    image.setPixel(1, 0, middlePixelColor);
    image.setPixel(2, 0, rightPixelColor);

    assignPixelsToLatestNodes(image);
    image.connectPixels(1, 0, 2, 0);

    auto leftPixelNode = makeNode(0u, leftPixelColor);
    auto rightPixelNode = makeNode(0u, rightPixelColor, leftPixelNode);
    auto middlePixelNode = makeNode(0u, middlePixelColor, rightPixelNode);

    verifyNode(image.getNodeOfPixel(0, 0), *leftPixelNode);
    verifyNode(image.getNodeOfPixel(1, 0), *middlePixelNode);
    verifyNode(image.getNodeOfPixel(2, 0), *rightPixelNode);
}

TEST_F(MaxTreeImageTest, nodesAreMergedWhenPixelsAreConnected) {
    DummyMaxTreeImageType image(3, 1);

    auto leftPixelColor = PixelType{ 14 };
    auto middlePixelColor = PixelType{ 16 };
    auto rightPixelColor = PixelType{ 15 };

    image.setPixel(0, 0, leftPixelColor);
    image.setPixel(1, 0, middlePixelColor);
    image.setPixel(2, 0, rightPixelColor);

    assignPixelsToLatestNodes(image);

    auto leftPixelNode = makeNode(0u, leftPixelColor);
    auto middlePixelNode = makeNode(0u, middlePixelColor, leftPixelNode);
    auto rightPixelNode = makeNode(0u, rightPixelColor, leftPixelNode);

    verifyNode(image.getNodeOfPixel(0, 0), leftPixelNode);
    verifyNode(image.getNodeOfPixel(1, 0), middlePixelNode);
    verifyNode(image.getNodeOfPixel(2, 0), rightPixelNode);
}

TEST_F(MaxTreeImageTest, getterMethodsAreConstQualified) {
    using GetPixelValueMethodSignature =
            PixelType (DummyMaxTreeImageType::*) (unsigned int, unsigned int)
                    const;

    assertThat(&DummyMaxTreeImageType::getWidth).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getHeight).isConstMethod();
    assertThat((GetPixelValueMethodSignature)
            &DummyMaxTreeImageType::getPixelValue).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getNodeOfPixel).isConstMethod();
}
