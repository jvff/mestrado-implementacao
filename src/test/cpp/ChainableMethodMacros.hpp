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

#define CHAIN_I(MethodName, ElementType, ParameterName) \
    ThisType& MethodName(std::initializer_list<ElementType> ParameterName) { \
        unchainable_##MethodName(ParameterName); \
\
        return *this; \
    } \
\
    void unchainable_##MethodName( \
            std::initializer_list<ElementType> ParameterName)

#define CHAIN_PARENT_METHOD(MethodName) \
    template <typename... ParameterTypes> \
    ThisType& MethodName(ParameterTypes... parameters) { \
        SuperClass::MethodName(parameters...); \
\
        return *this; \
    } \

#endif
