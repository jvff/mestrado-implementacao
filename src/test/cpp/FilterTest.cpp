#include <fakeit.hpp>

#include "FilterTest.hpp"

using namespace fakeit;

TEST_F(FilterTest, classIsntAbstract) {
    auto filter = new FakeDummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST_F(FilterTest, destructorIsVirtual) {
    testIfDestructorIsVirtual<DummyFilter, FakeDummyFilter>();
}

TEST_F(FilterTest, imageFactoryWasCreated) {
    auto fakeFilter = new FakeDummyFilter();
    auto factory = fakeFilter->getImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete fakeFilter;
}

TEST_F(FilterTest, destinationImageDimensionsAreRequested) {
    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy(fakeFilter);
    Mock<SourceImageType> sourceImageMock;
    auto& imageFactoryMock = fakeFilter.getImageFactoryMock();
    auto& filter = filterSpy.get();
    auto* sourceImage = &sourceImageMock.get();

    When(Method(filterSpy, getDestinationImageWidth).Using(sourceImage))
        .Return(1);
    When(Method(filterSpy, getDestinationImageHeight).Using(sourceImage))
        .Return(1);
    When(Method(imageFactoryMock, createImage)).Return(NULL);

    filter.apply(sourceImage);

    Verify(Method(filterSpy, getDestinationImageWidth).Using(sourceImage));
    Verify(Method(filterSpy, getDestinationImageHeight).Using(sourceImage));
}

TEST_F(FilterTest, imageFactoryIsUsed) {
    int width = 211;
    int height = 102;
    DestinationImageType* destinationImage = NULL;
    FakeDummyFilter fakeFilter;
    Mock<FakeDummyFilter> filterSpy(fakeFilter);
    Mock<SourceImageType> sourceImageMock;
    Mock<DestinationImageType> destinationImageMock;
    auto& imageFactoryMock = fakeFilter.getImageFactoryMock();
    auto& filter = filterSpy.get();
    auto* sourceImage = &sourceImageMock.get();
    auto* createdDestinationImage = &destinationImageMock.get();

    When(Method(filterSpy, getDestinationImageWidth).Using(sourceImage))
        .Return(width);
    When(Method(filterSpy, getDestinationImageHeight).Using(sourceImage))
        .Return(height);
    When(Method(imageFactoryMock, createImage).Using(width, height))
        .Return(createdDestinationImage);

    destinationImage = filter.apply(sourceImage);

    EXPECT_EQ(createdDestinationImage, destinationImage);

    Verify(Method(filterSpy, getDestinationImageWidth).Using(sourceImage));
    Verify(Method(filterSpy, getDestinationImageHeight).Using(sourceImage));
    Verify(Method(imageFactoryMock, createImage).Using(width, height));
}
