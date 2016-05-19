#ifndef OPEN_C_L_KERNEL_PARAMETERS_WRAPPER_FOR_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_WRAPPER_FOR_HPP

#include <typeinfo>

#include "OpenCLKernelParametersWrapper.hpp"

template <typename T>
class WrapperFor : public Wrapper {
private:
    T value;

public:
    WrapperFor(const T& value) : value(value) {
    }

    virtual T& operator*() {
        return value;
    }

    virtual bool operator==(const Wrapper& otherWrapper) const override {
        try {
            return *this == dynamic_cast<const WrapperFor<T>&>(otherWrapper);
        } catch (const std::bad_cast&) {
            return false;
        }
    }

    virtual bool operator==(const WrapperFor<T>& otherWrapper) const {
        return value == otherWrapper.value;
    }
};

#endif
