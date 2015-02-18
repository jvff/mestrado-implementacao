#include <cppunit/extensions/HelperMacros.h>

#include "Image.h"

class ImageTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ImageTest);
	CPPUNIT_TEST(testSinglePixel);
	CPPUNIT_TEST(testSingleRedPixel);
	CPPUNIT_TEST(testTwoPixels);
	CPPUNIT_TEST(testTwoPixelsWithDifferentColors);
        CPPUNIT_TEST(testRedGreenBlueRect);
    CPPUNIT_TEST_SUITE_END();

public:
    void testSinglePixel() {
	testSinglePixel(10);
    }

    void testSingleRedPixel() {
	testSinglePixel(0xFF0000);
    }

    void testSinglePixel(int color) {
	testPixelsWithSameColor(1, 1, color);
    }

    void testTwoPixels() {
	testPixelsWithSameColor(2, 1, 10);
    }

    void testTwoPixelsWithDifferentColors() {
	int colors[] = { 10, 20 };

	testPixels(2, 1, colors);
    }

    void testRedGreenBlueRect() {
	int width = 9;
	int height = 5;
	int colors[width * height];
	int *colorIterator = &colors[0];

	for (int x = 0; x < width; ++x) {
	    for (int y = 0; y < height; ++y) {
		switch (y % 5) {
		    case 0:
		    case 1:
		    case 2:
			*colorIterator++ = 0xFF << (2 * (x % 3));
			break;
		    case 3:
			*colorIterator++ = 0x00000000;
			break;
		    case 4:
			*colorIterator++ = 0xFFFFFFFF;
			break;
		};
	    }
	}

	testPixels(width, height, colors);
    }

    void testPixelsWithSameColor(int width, int height, int color) {
        Image image(width, height);

	for (int x = 0; x < width; ++x) {
	    for (int y = 0; y < height; ++y)
		image.setPixel(x, y, color);
	}

	for (int x = 0; x < width; ++x) {
	    for (int y = 0; y < height; ++y)
		CPPUNIT_ASSERT(image.getPixel(x, y) == color);
	}
    }

    void testPixels(int width, int height, const int colors[]) {
        Image image(width, height);
	const int* colorIterator = &colors[0];

	for (int x = 0; x < width; ++x) {
	    for (int y = 0; y < height; ++y)
		image.setPixel(x, y, *(colorIterator++));
	}

	colorIterator = &colors[0];

	for (int x = 0; x < width; ++x) {
	    for (int y = 0; y < height; ++y) {
		CPPUNIT_ASSERT_EQUAL(image.getPixel(x, y), *(colorIterator++));
	    }
	}
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
