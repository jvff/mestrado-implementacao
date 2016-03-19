#ifndef ABSTRACT_FILTER_TEST_HPP
#define ABSTRACT_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "fakeit.hpp"

#include "AbstractFilter.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeAbstractFilter.hpp"
#include "FakeImageMockProxy.hpp"
#include "RefTo.hpp"

class AbstractFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImageMockProxy<DestinationPixelType>;
    using DummyFilter = AbstractFilter<SourceImageType, DestinationImageType>;
    using FakeDummyFilter = FakeAbstractFilter<SourceImageType,
            DestinationImageType>;

protected:
    unsigned int expectedWidth;
    unsigned int expectedHeight;

    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy;
    Mock<SourceImageType> sourceImageMock;

    DummyFilter& filter;
    const SourceImageType& sourceImage;

protected:
    AbstractFilterTest() : filterSpy(fakeFilter), filter(filterSpy.get()),
            sourceImage(sourceImageMock.get()) {
    }

    ~AbstractFilterTest() noexcept {
    }

    void expectImageCreation(unsigned int width, unsigned int height) {
        expectedWidth = width;
        expectedHeight = height;

        prepareFilterSpy();
        prepareSourceImageMock();
    }

    void verifyImageWasCreated() {
        Verify(Method(filterSpy, createDestinationImage)
            .Using(RefTo(sourceImage)));
    }

private:
    void prepareFilterSpy() {
        spyCreateDestinationImageMethod();
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
