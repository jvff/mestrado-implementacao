#ifndef IMPLEMENTATION_TEST_REGISTRATOR_HPP
#define IMPLEMENTATION_TEST_REGISTRATOR_HPP

#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

#include "../CustomParameterizedTestFactory.hpp"

#include "PixelTypeImageImplementations.hpp"
#include "PixelTypeImagePatterns.hpp"

namespace testing {
namespace internal {

template <template <typename> class FixtureClassTemplate,
        template <typename> class TestClassTemplate,
        typename PixelTypesTuple>
class ImplementationTestRegistrator {
private:
    template <typename PixelType>
    using Pattern = std::function<PixelType(unsigned int, unsigned int,
            unsigned int, unsigned int)>;

    static constexpr auto numberOfPixelTypes =
            std::tuple_size<PixelTypesTuple>::value;

    template <int index, int size, typename ReturnType = void>
    using EnableForValidIndex =
            typename std::enable_if<index < size, ReturnType>::type;

    template <int index, int size, typename ReturnType = void>
    using EnableForInvalidIndex =
            typename std::enable_if<index >= size, ReturnType>::type;

    template <int index, typename TupleType, typename ReturnType = void>
    using EnableForValidTupleIndex =
            EnableForValidIndex<index, std::tuple_size<TupleType>::value,
                    ReturnType>;

    template <int index, typename TupleType, typename ReturnType = void>
    using EnableForInvalidTupleIndex =
            EnableForInvalidIndex<index, std::tuple_size<TupleType>::value,
                    ReturnType>;

    template <int index>
    using EnableForValidPixelTypeIndex =
            EnableForValidTupleIndex<index, PixelTypesTuple, bool>;

    template <int index>
    using EnableForInvalidPixelTypeIndex =
            EnableForInvalidTupleIndex<index, PixelTypesTuple, bool>;

public:
    bool registerTests(const std::string& testCaseName,
            const std::string& testName) {
        return registerTestsForSinglePixelType<0>(testCaseName, testName);
    }

private:
    template <int pixelTypeIndex>
    EnableForInvalidPixelTypeIndex<pixelTypeIndex>
    registerTestsForSinglePixelType(const std::string&, const std::string&) {
        return true;
    }

    template <int pixelTypeIndex>
    EnableForValidPixelTypeIndex<pixelTypeIndex>
    registerTestsForSinglePixelType(const std::string& testCaseName,
            const std::string& testName) {
        using PixelType =
                typename std::tuple_element<pixelTypeIndex, PixelTypesTuple>
                        ::type;

        constexpr auto nextPixelTypeIndex = pixelTypeIndex + 1;

        registerTestsForPixelType<PixelType>(testCaseName, testName);

        return registerTestsForSinglePixelType<nextPixelTypeIndex>(testCaseName,
                testName);
    }

    template <typename PixelType>
    void registerTestsForPixelType(const std::string& testCaseName,
            const std::string& testName) {
        using Implementations = PixelTypeImageImplementations<PixelType>;

        constexpr auto numberOfImplementations =
                Implementations::getNumberOfImplementations();

        auto implementationNames = Implementations::getImplementationNames();

        registerTestsForImplementationAtIndex<PixelType, Implementations, 0,
                numberOfImplementations>(testCaseName, testName,
                        implementationNames);
    }

    template <typename PixelType, typename Implementations,
            int implementationIndex, int numberOfImplementations>
    EnableForInvalidIndex<implementationIndex, numberOfImplementations>
    registerTestsForImplementationAtIndex(const std::string&,
            const std::string&, const std::vector<std::string>&) {
    }

    template <typename PixelType, typename Implementations,
            int implementationIndex, int numberOfImplementations>
    EnableForValidIndex<implementationIndex, numberOfImplementations>
    registerTestsForImplementationAtIndex(const std::string& testCaseName,
            const std::string& testName,
            const std::vector<std::string>& implementationNames) {
        using ImplementationType = typename Implementations
                    ::template ImplementationAt<implementationIndex>;

        constexpr auto nextImplementationIndex = implementationIndex + 1;

        auto implementationName = implementationNames[implementationIndex];

        registerTestsForImplementation<PixelType, ImplementationType>(
                testCaseName, testName, implementationName);

        registerTestsForImplementationAtIndex<PixelType, Implementations,
                nextImplementationIndex, numberOfImplementations>(testCaseName,
                        testName, implementationNames);
    }

    template <typename PixelType, typename ImplementationType>
    void registerTestsForImplementation(const std::string& testCaseName,
            const std::string& testName,
            const std::string& implementationName) {
        auto patterns = PixelTypeImagePatterns<PixelType>();
        auto numberOfPatterns = patterns.getNumberOfPatterns();

        for (auto index = 0u; index < numberOfPatterns; ++index) {
            registerSingleTest<PixelType, ImplementationType>(testCaseName,
                    testName, implementationName,
                    patterns.getImagePattern(index));
        }
    }

    template <typename PixelType, typename ImplementationType>
    void registerSingleTest(const std::string& testCaseName,
            const std::string& testName, const std::string& implementationName,
            const Pattern<PixelType>& imagePattern) {
        using PatternType = Pattern<PixelType>;
        using FixtureClass = FixtureClassTemplate<ImplementationType>;
        using TestClass = TestClassTemplate<ImplementationType>;
        using TestFactory = CustomParameterizedTestFactory<TestClass,
                PatternType>;

        auto finalTestCaseName = testCaseName + "<" + implementationName + ">";

        MakeAndRegisterTestInfo(finalTestCaseName.c_str(), testName.c_str(),
                NULL, NULL, GetTypeId<FixtureClass>(), TestClass::SetUpTestCase,
                TestClass::TearDownTestCase, new TestFactory(imagePattern));
    }
};

}
}

#endif
