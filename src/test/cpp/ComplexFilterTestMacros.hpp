#ifndef COMPLEX_FILTER_TEST_MACROS_HPP
#define COMPLEX_FILTER_TEST_MACROS_HPP

#include <memory>

#include <gtest/gtest.h>

#define COMPLEX_FILTER_TEST_CASE(TestCase) \
    DECLARE_COMPLEX_FILTER_TEST_FIXTURE(TestCase); \
    OPEN_COMPLEX_FILTER_TEST_NAMESPACE(TestCase) \
    DECLARE_COMPLEX_FILTER_TEST_CASE_STATE(); \
    CREATE_COMPLEX_FILTER_TEST_FIXTURE_TEMPLATE_ALIAS(TestCase); \
    CREATE_COMPLEX_FILTER_TEST_FIXTURE_NAME_STRING(TestCase)

#define DECLARE_COMPLEX_FILTER_TEST_FIXTURE(TestCase) \
    template <typename TestDataWrapper> \
    class TestCase : public ::testing::Test { \
    protected: \
        template <typename T> \
        using TestData = typename TestDataWrapper::template TestData<T>; \
    }

#define OPEN_COMPLEX_FILTER_TEST_NAMESPACE(TestCase) \
    namespace GTEST_CASE_NAMESPACE_(TestCase) {

#define CLOSE_COMPLEX_FILTER_TEST_NAMESPACE(TestCase) \
    }

#define DECLARE_COMPLEX_FILTER_TEST_CASE_STATE() \
    static ::testing::internal::TypedTestCasePState testCasePState

#define CREATE_COMPLEX_FILTER_TEST_FIXTURE_TEMPLATE_ALIAS(TestCase) \
    template <typename T> \
    using TestFixtureTemplate = TestCase<T>

#define CREATE_COMPLEX_FILTER_TEST_FIXTURE_NAME_STRING(TestCase) \
    const std::string TestFixtureName = #TestCase

#define COMPLEX_FILTER_TEST(TestName) \
    CREATE_COMPLEX_FILTER_TEST_CLASS(TestName); \
    REGISTER_COMPLEX_FILTER_TEST_CLASS(TestName); \
    START_COMPLEX_FILTER_TEST_BODY(TestName)

#define CREATE_COMPLEX_FILTER_TEST_CLASS(TestName) \
    template <typename gtest_TypeParam_> \
    class TestName : public TestFixtureTemplate<gtest_TypeParam_> { \
    private: \
        using TestFixture = TestFixtureTemplate<gtest_TypeParam_>; \
        using TypeParam = gtest_TypeParam_; \
\
        template <typename T> \
        using TestData = typename TestFixture::template TestData<T>; \
\
        virtual void TestBody(); \
    }

#define REGISTER_COMPLEX_FILTER_TEST_CLASS(TestName) \
    static bool gtest_##TestName##_defined_ GTEST_ATTRIBUTE_UNUSED_ = \
            testCasePState.AddTestName(__FILE__, __LINE__, \
                    TestFixtureName.c_str(), #TestName)

#define START_COMPLEX_FILTER_TEST_BODY(TestCase) \
    template <typename gtest_TypeParam_> \
    void TestCase<gtest_TypeParam_>::TestBody()


#define REGISTER_COMPLEX_FILTER_TEST_CASE(TestCase, ...) \
    DECLARE_COMPLEX_FILTER_TEST_CASE_ALL_TESTS(TestCase, __VA_ARGS__); \
    CLOSE_COMPLEX_FILTER_TEST_NAMESPACE(TestCase) \
    REGISTER_COMPLEX_FILTER_TEST_CASE_TEST_NAMES(TestCase, __VA_ARGS__)

#define DECLARE_COMPLEX_FILTER_TEST_CASE_ALL_TESTS(TestCase, ...) \
    using gtest_AllTests_ = ::testing::internal::Templates<__VA_ARGS__>::type

#define REGISTER_COMPLEX_FILTER_TEST_CASE_TEST_NAMES(TestCase, ...) \
    static const char* const GTEST_REGISTERED_TEST_NAMES_(TestCase) = \
            GTEST_CASE_NAMESPACE_(TestCase)::testCasePState \
                    .VerifyRegisteredTestNames( __FILE__, __LINE__, \
                            #__VA_ARGS__)

#define INSTANTIATE_COMPLEX_FILTER_TEST_CASE(InstantiationName, TestCase, \
        TestDataClass) \
    CREATE_COMPLEX_FILTER_TEST_DATA_WRAPPER_CLASS(InstantiationName, TestCase, \
            TestDataClass); \
    INSTANTIATE_TYPED_TEST_CASE_P(InstantiationName, TestCase, \
            COMPLEX_FILTER_TEST_DATA_WRAPPER_NAME(InstantiationName, TestCase))

#define COMPLEX_FILTER_TEST_DATA_WRAPPER_NAME(InstantiationName, TestCase) \
    _gtest_##InstantiationName##_##TestCase##_TestDataWrapper

#define CREATE_COMPLEX_FILTER_TEST_DATA_WRAPPER_CLASS(InstantiationName, \
        TestCase, TestData) \
    class COMPLEX_FILTER_TEST_DATA_WRAPPER_NAME(InstantiationName, TestCase) { \
    public: \
        template <typename T> \
        using TestData = TestData<T>; \
    }

#endif
