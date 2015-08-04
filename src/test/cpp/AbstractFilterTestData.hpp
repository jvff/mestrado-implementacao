#ifndef ABSTRACT_FILTER_TEST_DATA_HPP
#define ABSTRACT_FILTER_TEST_DATA_HPP

#include <memory>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "AbstractTestData.hpp"

template <typename FilterType, typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
class AbstractFilterTestData : public AbstractTestData {
protected:
    using SourceImagePointer = std::unique_ptr<SourceImageType>;
    using DestinationImagePointer = std::unique_ptr<DestinationImageType>;

    unsigned int width;
    unsigned int height;

    unsigned int expectedWidth;
    unsigned int expectedHeight;

public:
    FilterType filter;
    SourceImagePointer sourceImage;
    DestinationImagePointer expectedImage;

public:
    virtual ~AbstractFilterTestData() {
    }

    void setDimensions(unsigned int newWidth, unsigned int newHeight) {
        if (stateIs(State::EMPTY)) {
            width = newWidth;
            height = newHeight;

            updateExpectedDimensions();

            sourceImage.reset(new SourceImageType(width, height));
            expectedImage.reset(new DestinationImageType(expectedWidth,
                        expectedHeight));

            state = State::READY;
        }
    }

protected:
    virtual void updateExpectedDimensions() {
        expectedWidth = width;
        expectedHeight = height;
    }

    void runTest() override {
        auto result = filter.apply(*sourceImage);

        assertThat(result).isEqualTo(*expectedImage);
    }
};

#endif
