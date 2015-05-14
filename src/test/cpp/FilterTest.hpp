#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "Filter.hpp"
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "VirtualDestructorTest.hpp"

using namespace fakeit;

class FilterTest : public testing::Test, protected VirtualDestructorTest {
protected:
    typedef DummyTypes<1> SourcePixelType;
    typedef DummyTypes<2> DestinationPixelType;
    typedef Image<SourcePixelType> SourceImageType;
    typedef SimpleArrayImage<DestinationPixelType> DestinationImageType;
    typedef Filter<SourcePixelType, DestinationPixelType, DestinationImageType>
            DummyFilter;
    typedef FakeFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType> FakeDummyFilter;
    typedef ImageFactory<DestinationImageType> DummyImageFactory;

    bool imageShouldHaveBeenCreated;
    unsigned int expectedWidth;
    unsigned int expectedHeight;

    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy;
    Mock<SourceImageType> sourceImageMock;
    Mock<DestinationImageType> destinationImageMock;
    Mock<DummyImageFactory>& imageFactoryMock;
    DummyFilter* filter;
    SourceImageType* sourceImage;
    DestinationImageType* destinationImage;

protected:
    FilterTest() : filterSpy(fakeFilter),
            imageFactoryMock(fakeFilter.getImageFactoryMock()) {
        filter = &filterSpy.get();
        sourceImage = &sourceImageMock.get();
        destinationImage = &destinationImageMock.get();
    }

    ~FilterTest() noexcept {
    }

    void SetUp() {
        imageShouldHaveBeenCreated = false;
    }

    void TearDown() {
        verifyMocks();
    }

    void expectImageCreation(unsigned int width, unsigned int height) {
        Spy(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType*, DestinationImageType*)));
        When(OverloadedMethod(filterSpy, apply,
                DestinationPixelType(unsigned int, unsigned int,
                    const SourceImageType*))
            .Using(Lt(width), Lt(height), sourceImage))
            .AlwaysDo([](unsigned int x, unsigned int y, const SourceImageType*)
                   -> DestinationPixelType { return {(int)(x * y)}; });
        When(Method(filterSpy, getDestinationImageWidth).Using(sourceImage))
            .Return(width);
        When(Method(filterSpy, getDestinationImageHeight).Using(sourceImage))
            .Return(height);
        When(Method(imageFactoryMock, createImage).Using(width, height))
            .Return(destinationImage);
        When(Method(destinationImageMock, getWidth)).Return(width);
        When(Method(destinationImageMock, getHeight)).Return(height);
        When(Method(destinationImageMock, setPixel)
            .Using(Lt(width), Lt(height), _)).AlwaysReturn();

        imageShouldHaveBeenCreated = true;
        expectedWidth = width;
        expectedHeight = height;
    }

    void verifyMocks() {
        if (imageShouldHaveBeenCreated)
            verifyImageWasCreated();
    }

    void verifyImageWasCreated() {
        Verify(Method(filterSpy, getDestinationImageWidth).Using(sourceImage));
        Verify(Method(filterSpy, getDestinationImageHeight).Using(sourceImage));
        Verify(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType*, DestinationImageType*))
            .Using(sourceImage, destinationImage));
        Verify(Method(imageFactoryMock, createImage)
            .Using(expectedWidth, expectedHeight));

        for (unsigned int x = 0; x < expectedWidth; ++x) {
            for (unsigned int y = 0; y < expectedHeight; ++y) {
                Verify(OverloadedMethod(filterSpy, apply,
                        DestinationPixelType(unsigned int, unsigned int,
                            const SourceImageType*)).Using(x, y, sourceImage));
                Verify(Method(destinationImageMock, setPixel)
                    .Using(x, y, {(int)(x*y)}));
            }
        }
    }
};

#endif
