#ifndef IMPLEMENTATION_TEST_MACROS_HPP
#define IMPLEMENTATION_TEST_MACROS_HPP

#include <functional>
#include <tuple>

#include <gtest/gtest.h>

#include "ImageImplementationTestUsingCoordinates.hpp"
#include "ImageImplementationTestUsingPixels.hpp"
#include "ImageImplementationTestUsingValues.hpp"
#include "ImplementationTestRegistration.hpp"

#define PIXEL_TYPES(...) \
    using PixelTypesTuple = std::tuple<__VA_ARGS__>

#define IMAGE_IMPLEMENTATION_TEST_CASE(TestCase) \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_FIXTURE(TestCase, UsingCoordinates); \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_FIXTURE(TestCase, UsingPixels); \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_FIXTURE(TestCase, UsingValues)

#define DECLARE_IMAGE_IMPLEMENTATION_TEST_FIXTURE(TestCase, Suffix) \
template <typename ImageType> \
class TestCase##_##Suffix \
        : public ImageImplementationTest##Suffix<ImageType, \
                typename ImageType::PixelType> { \
}

#define IMAGE_IMPLEMENTATION_TEST(TestCase, TestName) \
    MAKE_IMAGE_IMPLEMENTATION_TEST_NAMED(TestCase, TestName, \
            GTEST_TEST_CLASS_NAME_(TestCase, TestName))

#define MAKE_IMAGE_IMPLEMENTATION_TEST_NAMED(TestCase, TestName, ClassName) \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_CLASS(ClassName); \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASSES(TestCase, ClassName); \
    REGISTER_IMAGE_IMPLEMENTATION_TESTS(TestCase, TestName, ClassName); \
    START_IMAGE_IMPLEMENTATION_TEST_BODY(ClassName)

#define DECLARE_IMAGE_IMPLEMENTATION_TEST_CLASS(ClassName) \
template <template <typename> class FixtureClassTemplate, typename ImageType> \
class ClassName : public FixtureClassTemplate<ImageType> { \
protected: \
    using SuperClass = FixtureClassTemplate<ImageType>; \
    using PixelType = typename ImageType::PixelType; \
    using Pattern = std::function<PixelType(unsigned int, unsigned int, \
            unsigned int, unsigned int)>; \
\
protected: \
    Pattern pattern; \
\
public: \
    ClassName(Pattern pattern) : pattern(pattern) { \
    } \
\
    void TestBody(); \
\
private: \
    using SuperClass::createImage; \
    using SuperClass::testPixels; \
    using SuperClass::testPixelsUsingLambda; \
}

#define DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASSES(TestCase, ClassName) \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASS(TestCase, ClassName, \
            UsingCoordinates); \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASS(TestCase, ClassName, \
            UsingPixels); \
    DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASS(TestCase, ClassName, \
            UsingValues)

#define DECLARE_IMAGE_IMPLEMENTATION_TEST_SUBCLASS(TestCase, ClassName, \
        Suffix) \
template <typename ImageType> \
class ClassName##_##Suffix \
        : public ClassName<TestCase##_##Suffix, ImageType> { \
private: \
    using SuperClass = ClassName<TestCase##_##Suffix, ImageType>; \
\
    using Pattern = typename SuperClass::Pattern; \
\
private: \
    using SuperClass::pattern; \
\
public: \
    ClassName##_##Suffix(Pattern pattern) : SuperClass(pattern) { \
    } \
\
    using SuperClass::TestBody; \
}

#define REGISTER_IMAGE_IMPLEMENTATION_TESTS(TestCase, TestName, TestClass) \
    REGISTER_IMAGE_IMPLEMENTATION_TEST(TestCase, TestName, TestClass, \
            UsingCoordinates); \
    REGISTER_IMAGE_IMPLEMENTATION_TEST(TestCase, TestName, TestClass, \
            UsingPixels); \
    REGISTER_IMAGE_IMPLEMENTATION_TEST(TestCase, TestName, TestClass, \
            UsingValues)

#define REGISTER_IMAGE_IMPLEMENTATION_TEST(TestCase, TestName, TestClass, \
        Suffix) \
    bool gtest_##TestCase##_##TestName##Suffix##_registered_ \
            GTEST_ATTRIBUTE_UNUSED_ = \
        ::testing::internal::ImplementationTestRegistration \
                ::Register<TestCase##_##Suffix, TestClass##_##Suffix, \
                        PixelTypesTuple>(#TestCase #Suffix, #TestName)

#define START_IMAGE_IMPLEMENTATION_TEST_BODY(ClassName) \
template <template <typename> class FixtureClassTemplate, typename ImageType> \
void ClassName<FixtureClassTemplate, ImageType>::TestBody()

#endif
