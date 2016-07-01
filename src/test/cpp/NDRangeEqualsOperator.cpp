#include "NDRangeEqualsOperator.hpp"

bool operator==(const cl::NDRange& firstRange, const cl::NDRange& secondRange) {
    auto firstDimensions = firstRange.dimensions();
    auto secondDimensions = secondRange.dimensions();

    if (firstDimensions != secondDimensions)
        return false;

    auto dimensions = firstDimensions;

    const auto* firstValues = (const size_t*)firstRange;
    const auto* secondValues = (const size_t*)secondRange;

    for (auto index = 0u; index < dimensions; ++index) {
        if (firstValues[index] != secondValues[index])
            return false;
    }

    return true;
}
