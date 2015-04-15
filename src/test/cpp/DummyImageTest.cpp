#include <gtest/gtest.h>

#include "Image.hpp"

struct DummyType {
    int value;
};

class DummyImage : public Image<DummyType> {
public:
    DummyImage(int width, int height) : Image(width, height) {
    }

    virtual void setPixel(int x, int y, DummyType value) {
    }

    virtual DummyType getPixel(int x, int y) {
        static DummyType dummyValue = { 0 };

        return dummyValue;
    }
};

TEST(DummyImageTest, classIsntAbstract) {
    Image<DummyType>* image = new DummyImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}
