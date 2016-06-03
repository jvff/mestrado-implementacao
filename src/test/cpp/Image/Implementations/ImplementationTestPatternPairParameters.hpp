#ifndef IMPLEMENTATION_TEST_PATTERN_PAIR_PARAMETERS_HPP
#define IMPLEMENTATION_TEST_PATTERN_PAIR_PARAMETERS_HPP

#include <tuple>
#include <vector>

#include "PixelTypeImagePatterns.hpp"

template <typename PixelType>
class ImplementationTestPatternPairParameters {
private:
    using Pattern = std::function<PixelType(unsigned int, unsigned int,
            unsigned int, unsigned int)>;

    using PatternPair = std::pair<Pattern, Pattern>;

public:
    using TestParameterType = PatternPair;

public:
    static std::vector<PatternPair> getTestParameters() {
        auto patternsHolder = PixelTypeImagePatterns<PixelType>();
        auto patterns = patternsHolder.getPatternVector();
        auto numberOfPatterns = patterns.size();
        auto parameters = std::vector<PatternPair>();

        for (auto index = 0u; index < numberOfPatterns; ++index) {
            generatePairsStartingAt(patterns, index, numberOfPatterns,
                    parameters);
        }

        return parameters;
    }

private:
    static void generatePairsStartingAt(const std::vector<Pattern>& patterns,
            unsigned int startingIndex, unsigned int numberOfPatterns,
            std::vector<PatternPair>& testParameters) {
        auto firstPattern = patterns[startingIndex];

        for (auto index = startingIndex + 1; index < numberOfPatterns; ++index)
            generatePair(firstPattern, patterns[index], testParameters);
    }

    static void generatePair(const Pattern& firstPattern,
            const Pattern& secondPattern,
            std::vector<PatternPair>& testParameters) {
        auto pair = std::make_pair(firstPattern, secondPattern);

        testParameters.push_back(pair);
    }
};

#endif
