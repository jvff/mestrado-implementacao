#ifndef VIRTUAL_DESTRUCTOR_TEST_HPP
#define VIRTUAL_DESTRUCTOR_TEST_HPP

#include <gtest/gtest.h>

#include "DestructorInterceptorFor.hpp"

class VirtualDestructorTest {
protected:
    template<class ClassToTest, class ClassToInstance = ClassToTest,
            typename... ConstructorArgs>
    static void testIfDestructorIsVirtual(ConstructorArgs... args) {
        auto interceptor = new DestructorInterceptorFor<ClassToInstance,
                ConstructorArgs...>(args...);
        bool destructorWasCalled = false;
        ClassToTest* virtualType = interceptor;

        interceptor->setDestructorListener(&destructorWasCalled);

        delete virtualType;

        EXPECT_TRUE(destructorWasCalled);
    }
};

#endif
