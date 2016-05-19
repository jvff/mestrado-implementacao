#ifndef OPEN_C_L_KERNEL_PARAMETERS_CAPTURE_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_CAPTURE_HPP

#include <memory>

template <typename T>
class Capture {
private:
    std::shared_ptr<std::shared_ptr<T> > valuePointer;

public:
    Capture() : valuePointer(new std::shared_ptr<T>) {
    }

    Capture<T>& operator=(const T& newValue) {
        auto& value = *valuePointer;

        value.reset(new T(newValue));

        return *this;
    }

    T& operator*() {
        return **valuePointer;
    }
};

#endif
