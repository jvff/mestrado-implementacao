#ifndef ABSTRACT_FILTER_TEST_DATA_HPP
#define ABSTRACT_FILTER_TEST_DATA_HPP

#include <memory>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "AbstractImageTransformationTestData.hpp"

template <typename FilterType, typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
class AbstractFilterTestData : public AbstractImageTransformationTestData<
        SourcePixelType, DestinationPixelType, DestinationImageType,
        SourceImageType> {
public:
    FilterType filter;

protected:
    DestinationImageType transformImage() override {
        return filter.apply(*this->sourceImage);
    }
};

#endif
