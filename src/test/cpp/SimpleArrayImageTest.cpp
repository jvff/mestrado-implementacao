#include <gtest/gtest.h>

#include "MockSimpleArrayImage.hpp"

TEST(SimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image =
            new MockSimpleArrayImage<DummyType>(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST(SimpleArrayImageTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    auto mockImage = new DestructorInterceptorFor<
            SimpleArrayImage<DummyType>, int, int>(0, 0);
    SimpleArrayImage<DummyType>* image = mockImage;

    mockImage->setDestructorListener(&destructorWasCalled);

    delete image;

    EXPECT_TRUE(destructorWasCalled);
}
