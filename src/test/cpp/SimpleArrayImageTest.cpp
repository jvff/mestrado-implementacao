#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

TEST(SimpleArrayImageTest, classIsntAbstract) {
    AssertThat<SimpleArrayImage<DummyType> >
            ::isConstructible(With<unsigned int, unsigned int>());
}

TEST(SimpleArrayImageTest, destructorIsVirtual) {
    AssertThat<SimpleArrayImage<DummyType> >::hasVirtualDestructor();
}

TEST(SimpleArrayImageTest, isSettableWithLambdaExpression) {
    unsigned int width = 5;
    unsigned int height = 4;

    SimpleArrayImage<DummyType> image(width, height);

    image = [width] (unsigned int x, unsigned int y) -> DummyType {
        return DummyType{ (int)(y * width + x) };
    };

    DummyType pixelValue = {0};

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            assertThat(image.getPixel(x, y)).isEqualTo(pixelValue);

            ++pixelValue.value;
        }
    }
}
