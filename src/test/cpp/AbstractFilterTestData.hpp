#ifndef ABSTRACT_FILTER_TEST_DATA_HPP
#define ABSTRACT_FILTER_TEST_DATA_HPP

#include <memory>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "AbstractImageTransformationTestData.hpp"

template <typename FilterType, typename SourceImageType,
        typename DestinationImageType>
class AbstractFilterTestData : public AbstractImageTransformationTestData<
        SourceImageType, DestinationImageType> {
private:
    using SuperClass = AbstractImageTransformationTestData<SourceImageType,
            DestinationImageType>;

public:
    std::unique_ptr<FilterType> filter;

protected:
    template <typename... ParameterTypes>
    void initializeFilter(ParameterTypes... parameters) {
        filter.reset(new FilterType(parameters...));
    }

    void runTest() override {
        if (!filter)
            FAIL() << "Filter was not initialized";
        else
            SuperClass::runTest();
    }

    DestinationImageType transformImage() override {
        return filter->apply(*this->sourceImage);
    }
};

#endif
