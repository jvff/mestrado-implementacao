#ifndef IMPLEMENTATION_NAME_FOR_HPP
#define IMPLEMENTATION_NAME_FOR_HPP

#include <string>

#include "MinTreeImage.hpp"
#include "MaxTreeImage.hpp"
#include "OpenCLImage.hpp"
#include "SimpleArrayImage.hpp"

#define IMPLEMENTATION_NAME(ImplementationTemplate) \
template <> \
struct ImplementationNameFor<ImplementationTemplate> { \
    static std::string getNameUsing(const std::string& pixelTypeName) { \
        return std::string(#ImplementationTemplate) + "<" + pixelTypeName \
                + ">"; \
    } \
}

#define WRAPPER_IMPLEMENTATION_NAME(ImplementationTemplate, \
        WrappedImplementationTemplate) \
    WRAPPER_IMPLEMENTATION_NAME_USING_ALIAS(ImplementationTemplate, \
            WrappedImplementationTemplate, \
            ALIAS_FOR_WRAPPER_IMPLEMENTATION_NAME(ImplementationTemplate, \
                    WrappedImplementationTemplate))

#define ALIAS_FOR_WRAPPER_IMPLEMENTATION_NAME(OuterTemplate, InnerTemplate) \
    OuterTemplate##With##InnerTemplate

#define WRAPPER_IMPLEMENTATION_NAME_USING_ALIAS(ImplementationTemplate, \
        WrappedImplementationTemplate, Alias) \
    DECLARE_WRAPPER_IMPLEMENTATION_NAME_FOR_TEMPLATE_PARAMETER_ALIAS( \
            ImplementationTemplate, WrappedImplementationTemplate, Alias); \
    DECLARE_WRAPPER_IMPLEMENTATION_NAME_CLASS(ImplementationTemplate, \
            WrappedImplementationTemplate, Alias)

#define DECLARE_WRAPPER_IMPLEMENTATION_NAME_FOR_TEMPLATE_PARAMETER_ALIAS( \
        OuterTemplate, InnerTemplate, Alias) \
template <typename T> \
using Alias = OuterTemplate<InnerTemplate<T> >

#define DECLARE_WRAPPER_IMPLEMENTATION_NAME_CLASS(OuterTemplate, \
        InnerTemplate, Alias) \
template <> \
struct ImplementationNameFor<Alias> { \
    static std::string getNameUsing(const std::string& pixelTypeName) { \
        return std::string(#OuterTemplate) + "<" + #InnerTemplate + "<" \
                + pixelTypeName + "> >"; \
    } \
}

template <template <typename> class ImplementationTemplate>
struct ImplementationNameFor {
};

IMPLEMENTATION_NAME(OpenCLImage);
IMPLEMENTATION_NAME(SimpleArrayImage);

WRAPPER_IMPLEMENTATION_NAME(MinTreeImage, SimpleArrayImage);
WRAPPER_IMPLEMENTATION_NAME(MaxTreeImage, SimpleArrayImage);

#endif
