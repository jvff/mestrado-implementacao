#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

TEST(SimpleArrayImageTest, classIsntAbstract) {
    AssertThat<SimpleArrayImage<DummyType> >
            ::isConstructible(With<unsigned int, unsigned int>());
}

TEST(SimpleArrayImageTest, destructorIsVirtual) {
    AssertThat<SimpleArrayImage<DummyType> >::hasVirtualDestructor();
}
