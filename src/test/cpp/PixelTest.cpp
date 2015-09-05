#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Pixel.hpp"

#include "DummyTypes.hpp"

TEST(PixelTest, structTemplateExists) {
    AssertThat<Pixel<DummyType> >::isClassOrStruct();
}

TEST(PixelTest, hasValueMembers) {
    unsigned int x = 1;
    unsigned int y = 2;
    DummyType value = { 3 };

    Pixel<DummyType> pixel = { x, y, value };

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}

TEST(PixelTest, hasValueConstructor) {
    unsigned int x = 12;
    unsigned int y = 6;
    DummyType value = { 1000 };

    auto pixel = Pixel<DummyType>(x, y, value);

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}
