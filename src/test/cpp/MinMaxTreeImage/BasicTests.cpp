#include "MinMaxTreeImageTest.hpp"

SUB_TEST(BasicTests);

TEST_C(BasicTests, classTemplateExists) {
    AssertThat<DummyMinMaxTreeImageType>::isClassOrStruct();
}

TEST_C(BasicTests, isImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMinMaxTreeImageType>::isSubClass(Of<ParentImageClass>());
}

TEST_C(BasicTests, pixelTypeIsPubliclyAccessible) {
    using ImagePixelType = typename DummyMinMaxTreeImageType::PixelType;

    AssertThat<ImagePixelType>::isTheSame(As<PixelType>());
}

TEST_C(BasicTests, isConstructible) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;

    AssertThat<DummyMinMaxTreeImageType>::isConstructible(With<WidthParameter,
            HeightParameter>());
}

TEST_C(BasicTests, setsDimensions) {
    unsigned int width = 7539;
    unsigned int height = 401;

    DummyMinMaxTreeImageType image(width, height);

    assertThat(image.getWidth()).isEqualTo(width);
    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_C(BasicTests, updatesInternalImage) {
    unsigned int width = 6;
    unsigned int height = 4;

    DummyMinMaxTreeImageType image(width, height);

    paintImage(image);

    verifyPaintedImagePixels(image);
}

TEST_C(BasicTests, imagesAreAssignableToLambdaFunction) {
    unsigned int width = 8;
    unsigned int height = 7;

    DummyMinMaxTreeImageType image(width, height);

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

TEST_C(BasicTests, getterMethodsAreConstQualified) {
    using GetPixelValueMethodSignature =
            PixelType (DummyMinMaxTreeImageType::*) (unsigned int, unsigned int)
                    const;

    assertThat(&DummyMinMaxTreeImageType::getWidth).isConstMethod();
    assertThat(&DummyMinMaxTreeImageType::getHeight).isConstMethod();
    assertThat((GetPixelValueMethodSignature)
            &DummyMinMaxTreeImageType::getPixelValue).isConstMethod();
    assertThat(&DummyMinMaxTreeImageType::getPixelNode).isConstMethod();
}
