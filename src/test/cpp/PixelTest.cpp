#include "PixelTest.hpp"

TEST_F(PixelTest, structTemplateExists) {
    AssertThat<Pixel<DummyType> >::isClassOrStruct();
}

TEST_F(PixelTest, hasDefaultConstructor) {
    AssertThat<Pixel<DummyType> >::isConstructible(WithoutParameters());
}

TEST_F(PixelTest, hasValueMembers) {
    unsigned int x = 1;
    unsigned int y = 2;
    DummyType value = { 3 };

    Pixel<DummyType> pixel = { x, y, value };

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}

TEST_F(PixelTest, hasValueConstructor) {
    unsigned int x = 12;
    unsigned int y = 6;
    DummyType value = { 1000 };

    auto pixel = Pixel<DummyType>(x, y, value);

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}

TEST_F(PixelTest, hasCoordinateConstructor) {
    unsigned int x = 12;
    unsigned int y = 6;
    Coordinate coordinate(x, y);
    DummyType value = { 1000 };

    auto pixel = Pixel<DummyType>(coordinate, value);

    assertThat(pixel.x).isEqualTo(x);
    assertThat(pixel.y).isEqualTo(y);
    assertThat(pixel.value).isEqualTo(value);
}

TEST_F(PixelTest, isOrderable) {
    const Pixel<unsigned char> first(0, 0, 10);
    const Pixel<unsigned char> second(0, 0, 100);
    const Pixel<unsigned char> third(0, 0, 101);

    verifyOrder({first, second, third});
}

TEST_F(PixelTest, orderChecksAllFields) {
    const unsigned int left = 12;
    const unsigned int right = 94;
    const unsigned int up = 47;
    const unsigned int down = 89;
    const unsigned char deep = 2;
    const unsigned char shallow = 100;

    verifyOrder({
        Pixel<unsigned char>(left, up, deep),
        Pixel<unsigned char>(left, down, deep),
        Pixel<unsigned char>(right, up, deep),
        Pixel<unsigned char>(right, down, deep),
        Pixel<unsigned char>(left, up, shallow),
        Pixel<unsigned char>(left, down, shallow),
        Pixel<unsigned char>(right, up, shallow),
        Pixel<unsigned char>(right, down, shallow)
    });
}
