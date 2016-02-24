#ifndef BASIC_TESTS_HPP
#define BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "FilterImplementation.hpp"

#include "../../CustomTypedTestMacros.hpp"
#include "../../DummyTypes.hpp"
#include "../../FakeImage.hpp"

template <typename TypeParameter>
class AreaOpeningAndClosingMinMaxTreeImplementationTest
        : public ::testing::Test {
};

template <template <typename> class TreeTypeComparator>
struct AreaOpeningAndClosingMinMaxTreeImplementationTestAliases {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningMaxTreeImplementation<
            SourceImageType, DestinationImageType>;
};

#define TEST_C(testName) \
    TEST_C_HELPER(AreaOpeningAndClosingMinMaxTreeImplementationTest, testName)

#define TEST_C_HELPER(testFixture, testName) \
    CREATE_CUSTOM_TEST_CLASS(testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(testFixture, testName)

#define \
CREATE_CUSTOM_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using Aliases = TypeParameter; \
\
    using SourceImageType = typename Aliases::SourceImageType; \
    using DestinationImageType = typename Aliases::DestinationImageType; \
    using ImplementationClass = typename Aliases::ImplementationClass; \
\
    void TestBody(); \
}

#endif
