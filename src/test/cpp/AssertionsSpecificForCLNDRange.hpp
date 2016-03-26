#ifndef ASSERTIONS_SPECIFIC_FOR_C_L_N_D_RANGE_HPP
#define ASSERTIONS_SPECIFIC_FOR_C_L_N_D_RANGE_HPP

#include <CL/cl.hpp>

#include "asserts.hpp"

template <>
class AssertionsSpecificFor<cl::NDRange>
        : public CommonAssertions<cl::NDRange> {
private:
    using SuperClass = CommonAssertions<cl::NDRange>;

protected:
    using SuperClass::subject;

public:
    using SuperClass::SuperClass;

    ASSERTION_WITH_PARAM(isEqualTo, isSubjectEqualTo(parameter), parameter,
            subject)

private:
    bool isSubjectEqualTo(const cl::NDRange& parameter) {
        return dimensionsAreTheSameIn(parameter)
            && sizesAreTheSameIn(parameter);
    }

    bool dimensionsAreTheSameIn(const cl::NDRange& parameter) {
        return subject.dimensions() == parameter.dimensions();
    }

    bool sizesAreTheSameIn(const cl::NDRange& parameter) {
        auto dimensions = subject.dimensions();
        auto* subjectSizes = (const size_t*)subject;
        auto* parameterSizes = (const size_t*)parameter;

        for (auto index = 0u; index < dimensions; ++index) {
            if (subjectSizes[index] != parameterSizes[index])
                return false;
        }

        return true;
    }
};

#endif
