#ifndef CHAINABLE_METHOD_MACROS_HPP
#define CHAINABLE_METHOD_MACROS_HPP

#define CHAIN(MethodName, ...) \
    template <typename... ParameterTypes> \
    ThisType& MethodName(ParameterTypes... parameters) { \
        unchainable_##MethodName(parameters...); \
\
        return *this; \
    } \
\
    void unchainable_##MethodName(__VA_ARGS__)

#endif
