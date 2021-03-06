#ifndef ABSTRACT_IMAGE_TRANSFORMATION_TEST_DATA_HPP
#define ABSTRACT_IMAGE_TRANSFORMATION_TEST_DATA_HPP

#include <memory>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "AbstractTestData.hpp"
#include "TestImageFactory.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AbstractImageTransformationTestData : public AbstractTestData {
protected:
    using SourceImagePointer = std::unique_ptr<SourceImageType>;
    using DestinationImagePointer = std::unique_ptr<DestinationImageType>;

    TestImageFactory<SourceImageType> sourceImageFactory;
    TestImageFactory<DestinationImageType> destinationImageFactory;

    unsigned int width;
    unsigned int height;

    unsigned int expectedWidth;
    unsigned int expectedHeight;

public:
    SourceImagePointer sourceImage;
    DestinationImagePointer expectedImage;

public:
    virtual ~AbstractImageTransformationTestData() {
    }

    bool setDimensions(unsigned int newWidth, unsigned int newHeight) {
        if (stateIs(State::EMPTY)) {
            width = newWidth;
            height = newHeight;

            updateExpectedDimensions();

            sourceImage.reset(new SourceImageType(
                    sourceImageFactory.createImage(width, height)));
            expectedImage.reset(new DestinationImageType(
                    destinationImageFactory.createImage(width, height)));

            state = State::READY;

            return true;
        } else
            return false;
    }

protected:
    virtual void updateExpectedDimensions() {
        expectedWidth = width;
        expectedHeight = height;
    }

    void runTest() override {
        auto result = transformImage();

        assertThat(result).isEqualTo(*expectedImage);
    }

    virtual DestinationImageType transformImage() = 0;
};

#endif
