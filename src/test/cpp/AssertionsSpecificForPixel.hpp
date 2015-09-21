#ifndef ASSERTIONS_SPECIFIC_FOR_PIXEL_HPP
#define ASSERTIONS_SPECIFIC_FOR_PIXEL_HPP

#include "AssertionsSpecificFor.hpp"

#include "Pixel.hpp"

MSG(isBefore, "Expected pixel %s to be before %s");
MSG(isAfter, "Expected pixel %s to be after %s");
MSG(isNotBefore, "Expected pixel %s to not be before %s");
MSG(isNotAfter, "Expected pixel %s to not be after %s");

template <typename PixelType>
class AssertionsSpecificFor<Pixel<PixelType> >
        : public CommonAssertions<Pixel<PixelType> > {
protected:
    using CommonAssertions<Pixel<PixelType> >::subject;

public:
    AssertionsSpecificFor(const Pixel<PixelType>& pixel)
            : CommonAssertions<Pixel<PixelType> >(pixel) {
    }

    ASSERTION_WITH_PARAM(isBefore, subject.isBefore(parameter), subject,
            parameter)
    ASSERTION_WITH_PARAM(isAfter, subject.isAfter(parameter), subject,
            parameter)

    ASSERTION_WITH_PARAM(isNotBefore, !subject.isBefore(parameter), subject,
            parameter)
    ASSERTION_WITH_PARAM(isNotAfter, !subject.isAfter(parameter), subject,
            parameter)
};

#endif
