#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "FakeImageMockProxy.hpp"
#include "RefTo.hpp"

using namespace fakeit;

class FilterTest : public testing::Test {
protected:
    typedef DummyTypes<1> SourcePixelType;
    typedef DummyTypes<2> DestinationPixelType;
    typedef Image<SourcePixelType> SourceImageType;
    typedef FakeImageMockProxy<DestinationPixelType> DestinationImageType;
    typedef Filter<SourcePixelType, DestinationPixelType, DestinationImageType>
            DummyFilter;
    typedef FakeFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType> FakeDummyFilter;

    unsigned int expectedWidth;
    unsigned int expectedHeight;

    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy;
    Mock<SourceImageType> sourceImageMock;

    DummyFilter& filter;
    const SourceImageType& sourceImage;

protected:
    FilterTest() : filterSpy(fakeFilter), filter(filterSpy.get()),
            sourceImage(sourceImageMock.get()) {
    }

    ~FilterTest() noexcept {
    }

    void expectImageCreation(unsigned int width, unsigned int height) {
        expectedWidth = width;
        expectedHeight = height;

        prepareFilterSpy();
        prepareSourceImageMock();
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

    void verifyApplyWasCalled(DestinationImageType& image) {
        Verify(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType&, DestinationImageType&))
            .Using(RefTo(sourceImage), RefTo(image)));
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

    void verifyAllPixelsWereSet(DestinationImageType& image) {
        auto& mock = image.getMock();

        for (unsigned int x = 0; x < expectedWidth; ++x) {
            for (unsigned int y = 0; y < expectedHeight; ++y)
                verifyPixelWasSet(mock, x, y);
        }
    }

    void verifyPixelWasSet(Mock<FakeImage<DestinationPixelType> >& mock,
            unsigned int x, unsigned int y) {
        DestinationPixelType pixelValue{(int)(x * y)};

        Verify(Method(mock, setPixel).Using(x, y, pixelValue));
    }

private:
    void prepareFilterSpy() {
        spyApplyMethod();
        spyGetDestinationImageDimensionsMethods();
        spyCreateDestinationImageMethod();
        mockPerPixelApplyMethod();
    }

    void spyApplyMethod() {
        Spy(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType&, DestinationImageType&)));
    }

    void spyGetDestinationImageDimensionsMethods() {
        Spy(Method(filterSpy, getDestinationImageWidth)
            .Using(RefTo(sourceImage)));
        Spy(Method(filterSpy, getDestinationImageHeight)
            .Using(RefTo(sourceImage)));
    }

    void spyCreateDestinationImageMethod() {
        Spy(Method(filterSpy, createDestinationImage));
    }

    void mockPerPixelApplyMethod() {
        When(OverloadedMethod(filterSpy, apply,
                DestinationPixelType(unsigned int, unsigned int,
                    const SourceImageType&))
            .Using(Lt(expectedWidth), Lt(expectedHeight), RefTo(sourceImage)))
            .AlwaysDo([](unsigned int x, unsigned int y, const SourceImageType&)
                   -> DestinationPixelType { return { (int)(x * y)}; });
    }

    void prepareSourceImageMock() {
        When(Method(sourceImageMock, getWidth)).Return(expectedWidth);
        When(Method(sourceImageMock, getHeight)).Return(expectedHeight);
    }
};

#endif
