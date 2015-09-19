#ifndef ASSERTIONS_SPECIFIC_FOR_COORDINATE_HPP
#define ASSERTIONS_SPECIFIC_FOR_COORDINATE_HPP

#include "AssertionsSpecificFor.hpp"

#include "Coordinate.hpp"

MSG(isBefore, "Expected coordinate %s to be before %s");
MSG(isAfter, "Expected coordinate %s to be after %s");

template <>
class AssertionsSpecificFor<Coordinate> : public CommonAssertions<Coordinate> {
public:
    AssertionsSpecificFor(const Coordinate& coordinate)
            : CommonAssertions<Coordinate>(coordinate) {
    }

    ASSERTION_WITH_PARAM(isBefore, subject.isBefore(parameter), subject,
            parameter)
    ASSERTION_WITH_PARAM(isAfter, subject.isAfter(parameter), subject,
            parameter)
};

#endif
