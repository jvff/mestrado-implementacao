#ifndef ABSTRACT_FILTER_IMPLEMENTATION_TEST_DATA_HPP
#define ABSTRACT_FILTER_IMPLEMENTATION_TEST_DATA_HPP

#include <memory>

#include "asserts.hpp"

#include "AbstractImageTransformationTestData.hpp"

template <typename FilterImplementationType, typename SourceImageType,
        typename DestinationImageType>
class AbstractFilterImplementationTestData :
        public AbstractImageTransformationTestData<SourceImageType,
            DestinationImageType> {
protected:
    using SuperClass = AbstractImageTransformationTestData<SourceImageType,
            DestinationImageType>;
    using DestinationImagePointer =
            typename SuperClass::DestinationImagePointer;

public:
    DestinationImagePointer destinationImage;

public:
    void setDimensions(unsigned int newWidth, unsigned int newHeight) {
        if (SuperClass::setDimensions(newWidth, newHeight))
            createDestinationImage();
    }

protected:
    DestinationImageType transformImage() override {
        auto filterImplementation = FilterImplementationType(*this->sourceImage,
                *destinationImage);

        filterImplementation.apply();

        return *destinationImage;
    }

private:
    void createDestinationImage() {
        auto width = this->expectedWidth;
        auto height = this->expectedHeight;

        destinationImage.reset(new DestinationImageType(width, height));
    }
};

#endif
