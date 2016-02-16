#ifndef MAX_TREE_IMAGE_TEST_HPP
#define MAX_TREE_IMAGE_TEST_HPP

#include <functional>

#include "../CustomTypedTestMacros.hpp"

#include "AbstractFixture.hpp"

using nodeLevelComparatorTypes = ::testing::Types<std::less<DummyType> >;

#define SUB_TEST(testFixture) \
    CREATE_EMPTY_MAX_TREE_IMAGE_TEST_FIXTURE(MaxTreeImage##testFixture); \
    TYPED_TEST_CASE(MaxTreeImage##testFixture, nodeLevelComparatorTypes)

#define CREATE_EMPTY_MAX_TREE_IMAGE_TEST_FIXTURE(testFixture) \
template <typename TypeParameter> \
class testFixture : public MaxTreeImageTest<TypeParameter> { \
}

#define TEST_C(testFixture, testName) \
    CREATE_MAX_TREE_IMAGE_TEST_CLASS(MaxTreeImage##testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeImage##testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeImage##testFixture, testName)

#define CREATE_MAX_TREE_IMAGE_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
\
    using DummyMaxTreeImageType = typename SuperClass::DummyMaxTreeImageType; \
    using PixelType = typename SuperClass::PixelType; \
    using TreeNodePointer = typename SuperClass::TreeNodePointer; \
    using TreeNodeType = typename SuperClass::TreeNodeType; \
\
    using SuperClass::assignPixelsToLatestNodes; \
    using SuperClass::fillImage; \
    using SuperClass::makeNode; \
    using SuperClass::paintImage; \
    using SuperClass::verifyNode; \
    using SuperClass::verifyNodes; \
    using SuperClass::verifyPaintedImagePixels; \
\
    virtual void TestBody(); \
}

#endif
