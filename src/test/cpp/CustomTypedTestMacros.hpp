#ifndef CUSTOM_TYPED_TEST_MACROS_HPP
#define CUSTOM_TYPED_TEST_MACROS_HPP

#define REGISTER_CUSTOM_TYPED_TEST(testFixture, testName) \
    bool gtest_##testFixture##_##testName##_registered_ \
        GTEST_ATTRIBUTE_UNUSED_ = ::testing::internal::TypeParameterizedTest< \
            testFixture, ::testing::internal::TemplateSel< \
                GTEST_TEST_CLASS_NAME_(testFixture, testName)>, \
            GTEST_TYPE_PARAMS_(testFixture)>::Register(\
                "", #testFixture, #testName, 0) \

#define START_CUSTOM_TYPED_TEST_BODY(testFixture, testName) \
template <typename TypeParameter> \
void GTEST_TEST_CLASS_NAME_(testFixture, testName)<TypeParameter>::TestBody()

#endif
