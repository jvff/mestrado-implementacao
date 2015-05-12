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
    typedef Image<DummyTypes<1> > SourceImageType;
    typedef SimpleArrayImage<DummyTypes<2> > DestinationImageType;
    typedef Filter<SourceImageType, DestinationImageType> DummyFilter;
    typedef FakeFilter<SourceImageType, DestinationImageType> FakeDummyFilter;
    typedef ImageFactory<DestinationImageType> DummyImageFactory;

    bool imageShouldHaveBeenCreated;
    int expectedWidth;
    int expectedHeight;
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

    void expectImageCreation(int width, int height) {
        When(Method(filterSpy, getDestinationImageWidth).Using(sourceImage))
            .Return(width);
        When(Method(filterSpy, getDestinationImageHeight).Using(sourceImage))
            .Return(height);
        When(Method(imageFactoryMock, createImage).Using(width, height))
            .Return(destinationImage);

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
        Verify(Method(imageFactoryMock, createImage)
            .Using(expectedWidth, expectedHeight));
    }
};

#endif
