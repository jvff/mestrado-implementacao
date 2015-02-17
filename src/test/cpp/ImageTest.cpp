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
        Image image(1, 1);

        image.setPixel(0, 0, color);

        CPPUNIT_ASSERT(image.getPixel(0, 0) == color);
    }

    void testTwoPixels() {
        Image image(2, 1);
	int color = 10;

        image.setPixel(0, 0, color);
        image.setPixel(1, 0, color);

        CPPUNIT_ASSERT(image.getPixel(0, 0) == color);
        CPPUNIT_ASSERT(image.getPixel(1, 0) == color);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
