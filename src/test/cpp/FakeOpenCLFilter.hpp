#ifndef FAKE_OPEN_C_L_FILTER_HPP
#define FAKE_OPEN_C_L_FILTER_HPP

#include "OpenCLFilter.hpp"

template <typename... TemplateParameters>
class FakeOpenCLFilter : public OpenCLFilter<TemplateParameters...> {
private:
    using SuperClass = OpenCLFilter<TemplateParameters...>;

public:
    using SuperClass::SuperClass;
    using SuperClass::getGlobalWorkSize;
};

#endif
