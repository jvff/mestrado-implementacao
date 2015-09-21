#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Pixel.hpp"

#include "AssertionsSpecificForPixel.hpp"
#include "DummyTypes.hpp"

TEST(PixelTest, structTemplateExists) {
    AssertThat<Pixel<DummyType> >::isClassOrStruct();
}

TEST(PixelTest, hasDefaultConstructor) {
    AssertThat<Pixel<DummyType> >::isConstructible(WithoutParameters());
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

TEST(PixelTest, hasCoordinateConstructor) {
    unsigned int x = 12;
    unsigned int y = 6;
    Coordinate coordinate(x, y);
    DummyType value = { 1000 };

    auto pixel = Pixel<DummyType>(coordinate, value);

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}

TEST(PixelTest, isOrderable) {
    const Pixel<unsigned char> first(0, 0, 10);
    const Pixel<unsigned char> second(0, 0, 100);
    const Pixel<unsigned char> third(0, 0, 101);

    assertThat(first).isBefore(second);
    assertThat(first).isBefore(third);
    assertThat(second).isBefore(third);

    assertThat(third).isAfter(first);
    assertThat(third).isAfter(second);
    assertThat(second).isAfter(first);

    assertThat(first).isNotAfter(second);
    assertThat(first).isNotAfter(third);
    assertThat(second).isNotAfter(third);

    assertThat(third).isNotBefore(first);
    assertThat(third).isNotBefore(second);
    assertThat(second).isNotBefore(first);

    assertThat(first).isNotBefore(first);
    assertThat(second).isNotBefore(second);
    assertThat(third).isNotBefore(third);
    assertThat(first).isNotAfter(first);
    assertThat(second).isNotAfter(second);
    assertThat(third).isNotAfter(third);
}
