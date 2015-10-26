#ifndef COMPLEX_FILTER_TEST_MACROS_HPP
#define COMPLEX_FILTER_TEST_MACROS_HPP

#include <memory>

#include <gtest/gtest.h>

#define COMPLEX_FILTER_TEST_CASE(TestCase) \
    DECLARE_COMPLEX_FILTER_TEST_FIXTURE(TestCase); \
    DECLARE_COMPLEX_FILTER_TEST_CASE(TestCase)

#define DECLARE_COMPLEX_FILTER_TEST_FIXTURE(TestCase) \
    template <typename TestDataWrapper> \
    class TestCase : public ::testing::Test { \
    protected: \
        template <typename T> \
        using TestData = typename TestDataWrapper::template TestData<T>; \
    }

#define DECLARE_COMPLEX_FILTER_TEST_CASE(TestCase) \
    TYPED_TEST_CASE_P(TestCase)

#define COMPLEX_FILTER_TEST(TestCase, TestName) \
    TYPED_TEST_P(TestCase, TestName)

#define REGISTER_COMPLEX_FILTER_TEST_CASE(TestCase, ...) \
    REGISTER_TYPED_TEST_CASE_P(TestCase, __VA_ARGS__)

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
