#include "MaxTreeImageTest.hpp"

TEST_F(MaxTreeImageTest, classTemplateExists) {
    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}

TEST_F(MaxTreeImageTest, isImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMaxTreeImageType>::isSubClass(Of<ParentImageClass>());
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

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto pixelValue = image.getPixelValue(x, y);
            auto expectedPixelValue = PixelType{ (int)(x + y * width) };

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}

TEST_F(MaxTreeImageTest, allowsAssigningToRootNode) {
    unsigned int width = 3;
    unsigned int height = 2;
    PixelType rootNodeLevel = { 10 };

    DummyMaxTreeImageType image(width, height);

    fillImage(image, rootNodeLevel);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y)
            image.assignPixelToLatestNode(x, y);
    }

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto node = image.getNodeOfPixel(x, y);

            assertThat(node.id).isEqualTo((unsigned int)0);
            assertThat(node.level).isEqualTo(rootNodeLevel);
            assertThat((bool)node.parent).isEqualTo(false);
        }
    }
}

TEST_F(MaxTreeImageTest, nodeParentChain) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x)
            image.assignPixelToLatestNode(x, y);
    }

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            const auto& node = image.getNodeOfPixel(x, y);
            std::shared_ptr<MaxTreeNode<PixelType> > parent = node.parent;
            PixelType level = { (int)(x + y * width) };

            assertThat(node.id).isEqualTo((unsigned int)0);
            assertThat(node.level).isEqualTo(level);

            for (--level.value; level.value >= 0; --level.value) {
                assertThat((bool)parent).isEqualTo(true);
                assertThat(parent->id).isEqualTo((unsigned int)0);
                assertThat(parent->level).isEqualTo(level);

                parent = parent->parent;
            }

            assertThat((bool)parent).isEqualTo(false);
        }
    }
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
    assertThat(&DummyMaxTreeImageType::getWidth).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getHeight).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getPixelValue).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getNodeOfPixel).isConstMethod();
}
