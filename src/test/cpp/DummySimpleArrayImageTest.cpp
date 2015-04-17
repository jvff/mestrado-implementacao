#include <gtest/gtest.h>

#include "SimpleArrayImage.hpp"

#include "DummyType.hpp"

class DummySimpleArrayImage : public SimpleArrayImage<DummyType> {
public:
    DummySimpleArrayImage(int width, int height) : SimpleArrayImage(width, height) {
    }
};

TEST(DummySimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image = new DummySimpleArrayImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}
