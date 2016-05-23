#ifndef CUSTOM_PARAMETERIZED_TEST_FACTORY_HPP
#define CUSTOM_PARAMETERIZED_TEST_FACTORY_HPP

#include <gtest/gtest.h>

namespace testing {
namespace internal {

template <class TestClass, typename ParamType>
class CustomParameterizedTestFactory : public TestFactoryBase {
private:
    const ParamType parameter;

public:
    CustomParameterizedTestFactory(const ParamType& testParameter) :
            parameter(testParameter) {
    }

    Test* CreateTest() override {
        return new TestClass(parameter);
    }
};

}
}

#endif
