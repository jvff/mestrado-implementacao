#ifndef AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP
#define AREA_OPENING_MAX_TREE_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningMaxTreeImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
public:
    AreaOpeningMaxTreeImplementation(unsigned int, const SourceImageType&,
            DestinationImageType&) {
    }

    void apply() override {
    }
};

#endif
