#ifndef DESTRUCTOR_INTERCEPTOR_FOR_HPP
#define DESTRUCTOR_INTERCEPTOR_FOR_HPP

#include <cstddef>

template <class InterceptedClass, typename... Args>
class DestructorInterceptorFor : public InterceptedClass {
private:
    bool* destructorWasCalled;

public:
    DestructorInterceptorFor(Args... args) : InterceptedClass(args...) {
        destructorWasCalled = NULL;
    }

    virtual ~DestructorInterceptorFor() {
        if (destructorWasCalled != NULL)
            *destructorWasCalled = true;
    }

    void setDestructorListener(bool* destructorListener) {
        destructorWasCalled = destructorListener;
    }
};

#endif
