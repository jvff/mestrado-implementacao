#ifndef MORPHOLOGICAL_GRADIENT_FILTER_IMPLEMENTATION_TESTS_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_IMPLEMENTATION_TESTS_HPP

#include <gtest/gtest.h>

#include "Image.hpp"
#include "OpenCLImage.hpp"
#include "SimpleArrayImage.hpp"

#include "MorphologicalGradientFilterTestData.hpp"

#include "../CustomTypedTestMacros.hpp"

template <typename Aliases>
class MorphologicalGradientFilterImplementationTests : public ::testing::Test {
};

template <template <typename> class SourceImageTemplate,
        template <typename> class DestinationImageTemplate>
struct MorphologicalGradientFilterImplementationTestAliases {
    template <typename PixelType>
    using SourceImageType = SourceImageTemplate<PixelType>;

    template <typename PixelType>
    using DestinationImageType = DestinationImageTemplate<PixelType>;
};

template <template <typename> class... TestParameters>
using TestAliases =
        MorphologicalGradientFilterImplementationTestAliases<TestParameters...>;

#define TEST_C(TestName) \
    CREATE_MORPH_GRAD_FILTER_IMPLEMENTATION_TEST_CLASS(TestName); \
    REGISTER_CUSTOM_TYPED_TEST(MorphologicalGradientFilterImplementationTests, \
            TestName); \
    START_CUSTOM_TYPED_TEST_BODY( \
            MorphologicalGradientFilterImplementationTests, TestName)

#define CREATE_MORPH_GRAD_FILTER_IMPLEMENTATION_TEST_CLASS(TestName) \
template <typename ImageTemplateHolder> \
class GTEST_TEST_CLASS_NAME_(MorphologicalGradientFilterImplementationTests, \
        TestName) : public MorphologicalGradientFilterImplementationTests< \
                ImageTemplateHolder> { \
private: \
    template <typename PixelType> \
    using SourceImageType = typename ImageTemplateHolder \
            ::template SourceImageType<PixelType>; \
\
    template <typename PixelType> \
    using DestinationImageType = typename ImageTemplateHolder \
            ::template DestinationImageType<PixelType>; \
\
    template <typename PixelType> \
    using TestData = MorphologicalGradientFilterTestData<PixelType, \
            DestinationImageType<PixelType>, SourceImageType<PixelType> >; \
\
public: \
    virtual void TestBody(); \
}

#endif
