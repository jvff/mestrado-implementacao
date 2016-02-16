#include "MaxTreeImageTest.hpp"

SUB_TEST(BasicTests);

TEST_C(BasicTests, classTemplateExists) {
    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}

TEST_C(BasicTests, isImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMaxTreeImageType>::isSubClass(Of<ParentImageClass>());
}

TEST_C(BasicTests, pixelTypeIsPubliclyAccessible) {
    using ImagePixelType = typename DummyMaxTreeImageType::PixelType;

    AssertThat<ImagePixelType>::isTheSame(As<PixelType>());
}

TEST_C(BasicTests, isConstructible) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;

    AssertThat<DummyMaxTreeImageType>::isConstructible(With<WidthParameter,
            HeightParameter>());
}

TEST_C(BasicTests, setsDimensions) {
    unsigned int width = 7539;
    unsigned int height = 401;

    DummyMaxTreeImageType image(width, height);

    assertThat(image.getWidth()).isEqualTo(width);
    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_C(BasicTests, updatesInternalImage) {
    unsigned int width = 6;
    unsigned int height = 4;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);

    verifyPaintedImagePixels(image);
}

TEST_C(BasicTests, imagesAreAssignableToLambdaFunction) {
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

TEST_C(BasicTests, getterMethodsAreConstQualified) {
    using GetPixelValueMethodSignature =
            PixelType (DummyMaxTreeImageType::*) (unsigned int, unsigned int)
                    const;

    assertThat(&DummyMaxTreeImageType::getWidth).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getHeight).isConstMethod();
    assertThat((GetPixelValueMethodSignature)
            &DummyMaxTreeImageType::getPixelValue).isConstMethod();
    assertThat(&DummyMaxTreeImageType::getPixelNode).isConstMethod();
}
