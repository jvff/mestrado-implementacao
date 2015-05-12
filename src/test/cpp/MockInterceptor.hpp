#ifndef MOCK_INTERCEPTOR_HPP
#define MOCK_INTERCEPTOR_HPP

#include <fakeit.hpp>

template <class C>
class MockInterceptor {
private:
    C* original;
    C*& intercepted;
    fakeit::Mock<C> replacement;

public:
    MockInterceptor(C*& intercepted) : intercepted(intercepted) {
        original = intercepted;
        intercepted = &replacement.get();
    }

    ~MockInterceptor() {
        intercepted = original;
    }

    C* getOriginal() {
        return original;
    }

    C& getReplacement() {
        return replacement.get();
    }

    fakeit::Mock<C>& getMock() {
        return replacement;
    }
};

#endif
