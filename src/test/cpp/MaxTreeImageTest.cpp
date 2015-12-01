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
    MaxTreeNode<PixelType> expectedRootNode;

    fillImage(image, rootNodeLevel);
    assignPixelsToLatestNodes(image);

    expectedRootNode.id = 0u;
    expectedRootNode.level = rootNodeLevel;

    verifyNodes(image, expectedRootNode);
}

TEST_F(MaxTreeImageTest, nodeParentChain) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    verifyNodes(image, [width] (unsigned int x, unsigned int y)
            -> MaxTreeNode<PixelType> {
        std::shared_ptr<MaxTreeNode<PixelType> > parent;
        MaxTreeNode<PixelType> expectedNode;
        int level = x + y * width;

        expectedNode.id = 0u;
        expectedNode.level = PixelType{ level };

        for (auto parentLevel = 0; parentLevel < level; ++parentLevel) {
            auto grandParent = parent;

            parent.reset(new MaxTreeNode<PixelType>);
            parent->id = 0u;
            parent->level = PixelType{ parentLevel };
            parent->parent = grandParent;
        }

        expectedNode.parent = parent;

        return expectedNode;
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

    verifyNodes(image, [background, foreground] (unsigned int x, unsigned int y)
            -> MaxTreeNode<PixelType> {
        MaxTreeNode<PixelType> expectedNode;

        if (x == y) {
            expectedNode.id = 0u;
            expectedNode.level = background;
        } else {
            if (x == 1)
                expectedNode.id = 0u;
            else
                expectedNode.id = 1u;

            expectedNode.level = foreground;

            expectedNode.parent.reset(new MaxTreeNode<PixelType>);
            expectedNode.parent->id = 0u;
            expectedNode.parent->level = background;
        }

        return expectedNode;
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
