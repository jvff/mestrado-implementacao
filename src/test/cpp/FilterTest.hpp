#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "Filter.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeFilter.hpp"
#include "FakeImageMockProxy.hpp"
#include "RefTo.hpp"

using namespace fakeit;

class FilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImageMockProxy<DestinationPixelType>;
    using DummyFilter = Filter<SourceImageType, DestinationImageType>;
    using FakeDummyFilter = FakeFilter<SourceImageType, DestinationImageType>;

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
            .Using(RefTo(sourceImage)));
    }

    void verifyApplyWasCalled(DestinationImageType& image) {
        Verify(OverloadedMethod(filterSpy, apply,
                void(const SourceImageType&, DestinationImageType&))
            .Using(RefTo(sourceImage), RefTo(image)));
    }

private:
    void prepareFilterSpy() {
        spyApplyMethod();
        spyGetDestinationImageDimensionsMethods();
        spyCreateDestinationImageMethod();
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

    void prepareSourceImageMock() {
        When(Method(sourceImageMock, getWidth)).Return(expectedWidth);
        When(Method(sourceImageMock, getHeight)).Return(expectedHeight);
    }
};

#endif
