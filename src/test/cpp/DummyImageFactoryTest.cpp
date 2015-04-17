#include <gtest/gtest.h>

#include "ImageFactory.hpp"
#include "Image.hpp"

#include "DummyImageFactory.hpp"

TEST(DummyImageFactoryTest, classIsntAbstract) {
    ImageFactory<DummyImage> *factory = new DummyImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete factory;
}
