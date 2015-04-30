#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "SimpleArrayImageTest.hpp"

TEST_F(SimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image = new SimpleArrayImage<DummyType>(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST_F(SimpleArrayImageTest, destructorIsVirtual) {
    testIfDestructorIsVirtual<SimpleArrayImage<DummyType>,
            SimpleArrayImage<DummyType>, int, int>(0, 0);
}
