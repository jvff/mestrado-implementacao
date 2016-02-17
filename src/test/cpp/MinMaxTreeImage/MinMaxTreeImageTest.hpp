#ifndef MIN_MAX_TREE_IMAGE_TEST_HPP
#define MIN_MAX_TREE_IMAGE_TEST_HPP

#include <functional>

#include "../CustomTypedTestMacros.hpp"

#include "AbstractFixture.hpp"

using nodeLevelComparatorTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

#define SUB_TEST(testFixture) \
    CREATE_EMPTY_MIN_MAX_TREE_IMAGE_TEST_FIXTURE( \
            MinMaxTreeImage##testFixture); \
    TYPED_TEST_CASE(MinMaxTreeImage##testFixture, nodeLevelComparatorTypes)

#define CREATE_EMPTY_MIN_MAX_TREE_IMAGE_TEST_FIXTURE(testFixture) \
template <typename TypeParameter> \
class testFixture : public MinMaxTreeImageTest<TypeParameter> { \
}

#define TEST_C(testFixture, testName) \
    CREATE_MIN_MAX_TREE_IMAGE_TEST_CLASS(MinMaxTreeImage##testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeImage##testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeImage##testFixture, testName)

#define CREATE_MIN_MAX_TREE_IMAGE_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
\
    using DummyMinMaxTreeImageType = \
            typename SuperClass::DummyMinMaxTreeImageType; \
    using PixelType = typename SuperClass::PixelType; \
    using TreeNodePointer = typename SuperClass::TreeNodePointer; \
    using TreeNodeType = typename SuperClass::TreeNodeType; \
\
    using SuperClass::assignPixelsToLatestNodes; \
    using SuperClass::fillImage; \
    using SuperClass::makeLevelHeights; \
    using SuperClass::makeNode; \
    using SuperClass::paintImage; \
    using SuperClass::verifyNode; \
    using SuperClass::verifyNodes; \
    using SuperClass::verifyFilledImagePixels; \
    using SuperClass::verifyPaintedImagePixels; \
\
    virtual void TestBody(); \
}

#endif
