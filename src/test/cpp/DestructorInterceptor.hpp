#ifndef DESTRUCTOR_INTERCEPTOR_HPP
#define DESTRUCTOR_INTERCEPTOR_HPP

#include <cstddef>

class DestructorInterceptor {
private:
    bool* destructorWasCalled;

public:
    DestructorInterceptor() {
        destructorWasCalled = NULL;
    }

    virtual ~DestructorInterceptor() {
        if (destructorWasCalled != NULL)
            *destructorWasCalled = true;
    }

    void setDestructorListener(bool* destructorListener) {
        destructorWasCalled = destructorListener;
    }
};

template <class InterceptedClass, typename... Args>
class DestructorInterceptorFor : public DestructorInterceptor,
        public InterceptedClass {
public:
    DestructorInterceptorFor(Args... args) : InterceptedClass(args...) {
    }
};

#endif
