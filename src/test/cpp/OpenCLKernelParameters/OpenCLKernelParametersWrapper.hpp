#ifndef OPEN_C_L_KERNEL_PARAMETERS_WRAPPER_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_WRAPPER_HPP

class Wrapper {
public:
    virtual bool operator==(const Wrapper&) const {
        return false;
    }
};

#endif
