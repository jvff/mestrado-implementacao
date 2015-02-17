#include <cppunit/extensions/HelperMacros.h>

#include "Image.h"

class ImageTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ImageTest);
	CPPUNIT_TEST(testSinglePixel);
	CPPUNIT_TEST(testSingleRedPixel);
	CPPUNIT_TEST(testTwoPixels);
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
