#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "RefTo.hpp"

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

    unsigned int expectedWidth;
    unsigned int expectedHeight;

    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy;
    Mock<SourceImageType> sourceImageMock;
    Mock<DestinationImageType> destinationImageMock;

    DummyFilter& filter;
    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

protected:
    FilterTest() : filterSpy(fakeFilter), filter(filterSpy.get()),
            sourceImage(sourceImageMock.get()),
            destinationImage(destinationImageMock.get()) {
    }

    ~FilterTest() noexcept {
    }

    void expectImageCreation(unsigned int width, unsigned int height) {
        expectedWidth = width;
        expectedHeight = height;

        prepareFilterSpy();
        prepareDestinationImageMock();
    }

    void verifyImageDimensionsWereRequested() {
        Verify(Method(filterSpy, getDestinationImageWidth)
                .Using(RefTo(sourceImage)));

        Verify(Method(filterSpy, getDestinationImageHeight)
                .Using(RefTo(sourceImage)));
    }

    void verifyImageWasCreated() {
        Verify(Method(filterSpy, createDestinationImage)
            .Using(expectedWidth, expectedHeight));
    }

    void verifyApplyWasCalled() {
        Verify(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType&, DestinationImageType&))
            .Using(RefTo(sourceImage), RefTo(destinationImage)));
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
                    const SourceImageType&))
            .Using(x, y, RefTo(sourceImage)));
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
        mockCreateDestinationImageMethod();
    }

    void spyApplyMethod() {
        Spy(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType&, DestinationImageType&)));
    }

    void mockPerPixelApplyMethod() {
        When(OverloadedMethod(filterSpy, apply,
                DestinationPixelType(unsigned int, unsigned int,
                    const SourceImageType&))
            .Using(Lt(expectedWidth), Lt(expectedHeight), RefTo(sourceImage)))
            .AlwaysDo([](unsigned int x, unsigned int y, const SourceImageType&)
                   -> DestinationPixelType { return { (int)(x * y)}; });
    }

    void mockGetDestinationImageDimensionsMethods() {
        When(Method(filterSpy, getDestinationImageWidth)
            .Using(RefTo(sourceImage)))
            .Return(expectedWidth);
        When(Method(filterSpy, getDestinationImageHeight)
            .Using(RefTo(sourceImage)))
            .Return(expectedHeight);
    }

    void mockCreateDestinationImageMethod() {
        When(Method(filterSpy, createDestinationImage)
            .Using(expectedWidth, expectedHeight))
            .Return(&destinationImage);
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
