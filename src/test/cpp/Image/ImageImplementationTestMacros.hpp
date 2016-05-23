#ifndef IMAGE_IMPLEMENTATION_TEST_MACROS_HPP
#define IMAGE_IMPLEMENTATION_TEST_MACROS_HPP

#include "ImageImplementationTestUsingCoordinates.hpp"
#include "ImageImplementationTestUsingPixels.hpp"
#include "ImageImplementationTestUsingValues.hpp"

#define IMAGE_IMPLEMENTATION_TEST_CASE(TestCaseName, PixelType, ...) \
    DECLARE_IMAGE_TYPES_ALIAS(TestCaseName, __VA_ARGS__); \
    DECLARE_PIXEL_TYPE_ALIAS(TestCaseName, PixelType); \
    DECLARE_TEST_CASE(TestCaseName, UsingCoordinates); \
    DECLARE_TEST_CASE(TestCaseName, UsingPixels); \
    DECLARE_TEST_CASE(TestCaseName, UsingValues)

#define DECLARE_IMAGE_TYPES_ALIAS(TestCaseName, ...) \
    using _gtest_##TestCaseName##_ImageTypes = ::testing::Types<__VA_ARGS__>

#define DECLARE_PIXEL_TYPE_ALIAS(TestCaseName, PixelType) \
    using _gtest_##TestCaseName##_PixelType = PixelType

#define DECLARE_TEST_CASE(TestCaseName, TypeName) \
    DECLARE_FIXTURE_CLASS(TestCaseName, TypeName); \
    DECLARE_TYPED_TEST_CASE(TestCaseName, TypeName)

#define DECLARE_FIXTURE_CLASS(TestCaseName, TypeName) \
    template <typename ImageType> \
    class TestCaseName##_##TypeName \
            : public ImageImplementationTest##TypeName<ImageType, \
                    _gtest_##TestCaseName##_PixelType> { \
    }

#define DECLARE_TYPED_TEST_CASE(TestCaseName, TypeName) \
    TYPED_TEST_CASE(TestCaseName##_##TypeName, \
            _gtest_##TestCaseName##_ImageTypes)

#define IMAGE_TEST(TestCaseName, TestName) \
    DECLARE_TEST_CLASS(TestCaseName, TestName); \
    REGISTER_TEST(TestCaseName, TestName); \
    START_TEST_BODY(TestCaseName, TestName)

#define DECLARE_TEST_CLASS(TestCaseName, TestName) \
    template <template <typename> class FixtureClass, typename ImageType> \
    class GTEST_TEST_CLASS_NAME_(TestCaseName, TestName) \
            : public FixtureClass<ImageType> { \
    protected: \
        virtual void TestBody(); \
    }

#define REGISTER_TEST(TestCaseName, TestName) \
    REGISTER_SUB_TEST(TestCaseName, TestName, UsingCoordinates); \
    REGISTER_SUB_TEST(TestCaseName, TestName, UsingPixels); \
    REGISTER_SUB_TEST(TestCaseName, TestName, UsingValues)

#define REGISTER_SUB_TEST(TestCaseName, TestName, TestType) \
    DECLARE_SPECIFIC_TEST_CLASS(TestCaseName, TestName, TestType); \
    REGISTER_SPECIFIC_TEST(TestCaseName, TestName, TestType)

#define DECLARE_SPECIFIC_TEST_CLASS(TestCaseName, TestName, TestType) \
    template <typename ImageType> \
    class GTEST_TEST_CLASS_NAME_(TestCaseName##_##TestType, TestName) \
            : public GTEST_TEST_CLASS_NAME_(TestCaseName, TestName) \
                    <TestCaseName##_##TestType, ImageType> { \
    private: \
        using TestFixture = TestCaseName##_##TestType<ImageType>; \
        using TypeParam = ImageType; \
        using SuperClass = GTEST_TEST_CLASS_NAME_(TestCaseName, TestName) \
                <TestCaseName##_##TestType, TypeParam>; \
    \
        using SuperClass::TestBody; \
    }

#define REGISTER_SPECIFIC_TEST(TestCaseName, TestName, TestType) \
    bool gtest_##TestCaseName##_##TestName##_##TestType##_registered_ \
            GTEST_ATTRIBUTE_UNUSED_ = \
                    ::testing::internal::TypeParameterizedTest< \
                            TestCaseName##_##TestType, \
                            ::testing::internal::TemplateSel< \
                                    GTEST_TEST_CLASS_NAME_( \
                                            TestCaseName##_##TestType, \
                                            TestName)>, \
                            GTEST_TYPE_PARAMS_(TestCaseName##_##TestType)> \
                    ::Register("", #TestCaseName "_" #TestType, #TestName, 0)

#define START_TEST_BODY(TestCaseName, TestName) \
    template <template <typename> class FixtureClass, typename ImageType> \
    void GTEST_TEST_CLASS_NAME_(TestCaseName, TestName)<FixtureClass, \
            ImageType>::TestBody()

#endif
