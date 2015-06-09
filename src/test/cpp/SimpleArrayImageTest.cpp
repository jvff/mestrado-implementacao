#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

TEST(SimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image = new SimpleArrayImage<DummyType>(0, 0);

    assertThat(image).isNotNull();

    delete image;
}

TEST(SimpleArrayImageTest, destructorIsVirtual) {
    AssertThat<SimpleArrayImage<DummyType> >::hasVirtualDestructor();
}
