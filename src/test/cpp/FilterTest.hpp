#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"

using namespace fakeit;

class FilterTest : public testing::Test {
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

    unsigned int expectedWidth;
    unsigned int expectedHeight;

    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy;
    Mock<SourceImageType> sourceImageMock;
    Mock<DestinationImageType> destinationImageMock;
    Mock<DummyImageFactory>& imageFactoryMock;

    DummyFilter& filter;
    SourceImageType* sourceImage;
    DestinationImageType* destinationImage;

protected:
    FilterTest() : filterSpy(fakeFilter),
            imageFactoryMock(fakeFilter.getImageFactoryMock()),
            filter(filterSpy.get()) {
        sourceImage = &sourceImageMock.get();
        destinationImage = &destinationImageMock.get();
    }

    ~FilterTest() noexcept {
    }

    void expectImageCreation(unsigned int width, unsigned int height) {
        expectedWidth = width;
        expectedHeight = height;

        prepareFilterSpy();
        prepareImageFactoryMock();
        prepareDestinationImageMock();
    }

    void verifyImageDimensionsWereRequested() {
        Verify(Method(filterSpy, getDestinationImageWidth).Using(sourceImage));
        Verify(Method(filterSpy, getDestinationImageHeight).Using(sourceImage));
    }

    void verifyImageWasCreated() {
        Verify(Method(imageFactoryMock, createImage)
            .Using(expectedWidth, expectedHeight));
    }

    void verifyApplyWasCalled() {
        Verify(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType*, DestinationImageType*))
            .Using(sourceImage, destinationImage));
    }

    void verifyApplyWasCalledOnEachPixel() {
        for (unsigned int x = 0; x < expectedWidth; ++x) {
            for (unsigned int y = 0; y < expectedHeight; ++y)
                verifyApplyWasCalledOnPixel(x, y);
        }
    }

    void verifyApplyWasCalledOnPixel(unsigned int x, unsigned int y) {
        Verify(OverloadedMethod(filterSpy, apply,
                DestinationPixelType(unsigned int, unsigned int,
                    const SourceImageType*))
            .Using(x, y, sourceImage));
    }

    void verifyAllPixelsWereSet() {
        for (unsigned int x = 0; x < expectedWidth; ++x) {
            for (unsigned int y = 0; y < expectedHeight; ++y)
                verifyPixelWasSet(x, y);
        }
    }

    void verifyPixelWasSet(unsigned int x, unsigned int y) {
        DestinationPixelType pixelValue{(int)(x * y)};

        Verify(Method(destinationImageMock, setPixel)
            .Using(x, y, pixelValue));
    }

private:
    void prepareFilterSpy() {
        spyApplyMethod();
        mockPerPixelApplyMethod();
        mockGetDestinationImageDimensionsMethods();
    }

    void spyApplyMethod() {
        Spy(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType*, DestinationImageType*)));
    }

    void mockPerPixelApplyMethod() {
        When(OverloadedMethod(filterSpy, apply,
                DestinationPixelType(unsigned int, unsigned int,
                    const SourceImageType*))
            .Using(Lt(expectedWidth), Lt(expectedHeight), sourceImage))
            .AlwaysDo([](unsigned int x, unsigned int y, const SourceImageType*)
                   -> DestinationPixelType { return {(int)(x * y)}; });
    }

    void mockGetDestinationImageDimensionsMethods() {
        When(Method(filterSpy, getDestinationImageWidth)
            .Using(sourceImage))
            .Return(expectedWidth);
        When(Method(filterSpy, getDestinationImageHeight)
            .Using(sourceImage))
            .Return(expectedHeight);
    }

    void prepareImageFactoryMock() {
        When(Method(imageFactoryMock, createImage)
            .Using(expectedWidth, expectedHeight))
            .Return(destinationImage);
    }

    void prepareDestinationImageMock() {
        mockDestinationImageDimensions();
        mockDestinationImageSetPixelMethod();
    }

    void mockDestinationImageDimensions() {
        When(Method(destinationImageMock, getWidth))
            .Return(expectedWidth);
        When(Method(destinationImageMock, getHeight))
            .Return(expectedHeight);
    }

    void mockDestinationImageSetPixelMethod() {
        When(Method(destinationImageMock, setPixel)
            .Using(Lt(expectedWidth), Lt(expectedHeight), _))
            .AlwaysReturn();
    }
};

#endif
