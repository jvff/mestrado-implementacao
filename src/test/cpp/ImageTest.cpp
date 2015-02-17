#include <cppunit/extensions/HelperMacros.h>

#include "Image.h"

class ImageTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ImageTest);
	CPPUNIT_TEST(testSinglePixel);
    CPPUNIT_TEST_SUITE_END();

public:
    void testSinglePixel() {
        Image image(1, 1);
        int color = 10;

        image.setPixel(0, 0, color);

        CPPUNIT_ASSERT(image.getPixel(0, 0) == color);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
