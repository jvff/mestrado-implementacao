#include "LuminanceFilterGrayscaleImageImplementationTest.hpp"

using TypeParameters = ::testing::Types<
        Aliases<Image<int>, SimpleArrayImage<int>, SimpleArrayImage<int> >,
        Aliases<OpenCLImage<int>, OpenCLImage<int>, OpenCLImage<int> > >;

TYPED_TEST_CASE(LuminanceFilterGrayscaleImageImplementationTest,
        TypeParameters);

TEST_C(doesntChangeImage) {
    using SourcePixelType = typename SourceImageType::PixelType;

    unsigned int width = 4;
    unsigned int height = 3;

    FilterType filter;
    auto realSourceImage = createSourceImage(width, height);
    const SourceImageType& sourceImage = realSourceImage;

    realSourceImage = [=] (unsigned int x, unsigned int y) -> SourcePixelType {
        return (int)(x + y * width);
    };

    auto resultingImage = filter.apply(sourceImage);

    assertThat(resultingImage).isEqualTo(sourceImage);
}
