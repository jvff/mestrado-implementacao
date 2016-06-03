#ifndef IMPLEMENTATION_TEST_REGISTRATION_HPP
#define IMPLEMENTATION_TEST_REGISTRATION_HPP

#include <string>

#include <gtest/gtest.h>

#include "ImplementationTestPatternPairParameters.hpp"
#include "ImplementationTestSinglePatternParameters.hpp"
#include "ImplementationTestRegistrator.hpp"

namespace testing {
namespace internal {

class ImplementationTestRegistration {
public:
    template <template <typename> class FixtureClassTemplate,
            template <typename> class TestClassTemplate,
            typename PixelTypesTuple>
    static bool Register(const std::string& testCaseName,
            const std::string& testName) {
        using Registrator = ImplementationTestRegistrator<FixtureClassTemplate,
                TestClassTemplate, ImplementationTestSinglePatternParameters,
                PixelTypesTuple>;

        auto registrator = Registrator();

        return registrator.registerTests(testCaseName, testName);
    }

    template <template <typename> class FixtureClassTemplate,
            template <typename> class TestClassTemplate,
            typename PixelTypesTuple>
    static bool RegisterWithPatternPairs(const std::string& testCaseName,
            const std::string& testName) {
        using Registrator = ImplementationTestRegistrator<FixtureClassTemplate,
                TestClassTemplate, ImplementationTestPatternPairParameters,
                PixelTypesTuple>;

        auto registrator = Registrator();

        return registrator.registerTests(testCaseName, testName);
    }
};

}
}

#endif
