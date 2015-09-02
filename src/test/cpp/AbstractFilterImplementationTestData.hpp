#ifndef ABSTRACT_FILTER_IMPLEMENTATION_TEST_DATA_HPP
#define ABSTRACT_FILTER_IMPLEMENTATION_TEST_DATA_HPP

#include <memory>
#include <type_traits>

#include "asserts.hpp"

#include "AbstractImageTransformationTestData.hpp"

template <typename FilterImplementationType, typename SourceImageType,
        typename DestinationImageType>
class AbstractFilterImplementationTestDataCommonCode :
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
    bool setDimensions(unsigned int newWidth, unsigned int newHeight) {
        if (SuperClass::setDimensions(newWidth, newHeight)) {
            createDestinationImage();

            return true;
        } else
            return false;
    }

protected:
    DestinationImageType transformImage() override {
        auto implementation = instantiateImplementation(*this->sourceImage,
                *destinationImage);

        implementation.apply();

        return *destinationImage;
    }

    virtual FilterImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) = 0;

private:
    void createDestinationImage() {
        auto width = this->expectedWidth;
        auto height = this->expectedHeight;

        destinationImage.reset(new DestinationImageType(width, height));
    }
};

template <typename FilterImplementationType, typename SourceImageType,
        typename DestinationImageType, typename ShouldEnable = void>
class AbstractFilterImplementationTestData
        : public AbstractFilterImplementationTestDataCommonCode<
                FilterImplementationType, SourceImageType,
                DestinationImageType> {
};

template <typename FilterImplementationType, typename SourceImageType,
        typename DestinationImageType>
class AbstractFilterImplementationTestData<FilterImplementationType,
        SourceImageType, DestinationImageType,
        typename std::enable_if<std::is_constructible<FilterImplementationType,
                const SourceImageType&, DestinationImageType&>::value>::type>
        : public AbstractFilterImplementationTestDataCommonCode<
                FilterImplementationType, SourceImageType,
                DestinationImageType> {
protected:
    FilterImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        return FilterImplementationType(sourceImage, destinationImage);
    }
};

#endif
