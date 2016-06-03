#ifndef IMPLEMENTATION_TEST_SINGLE_PATTERN_PARAMETERS_HPP
#define IMPLEMENTATION_TEST_SINGLE_PATTERN_PARAMETERS_HPP

#include <vector>

#include "PixelTypeImagePatterns.hpp"

template <typename PixelType>
class ImplementationTestSinglePatternParameters {
private:
    using Pattern = std::function<PixelType(unsigned int, unsigned int,
            unsigned int, unsigned int)>;

public:
    using TestParameterType = Pattern;

public:
    static std::vector<Pattern> getTestParameters() {
        auto patterns = PixelTypeImagePatterns<PixelType>();

        return patterns.getPatternVector();
    }
};

#endif
