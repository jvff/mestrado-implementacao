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
    DummyFilter& filter = filterSpy.get();
    SourceImageType* sourceImage = &sourceImageMock.get();

    When(Method(filterSpy, getDestinationImageWidth).Using(sourceImage))
        .Return(1);
    When(Method(filterSpy, getDestinationImageHeight).Using(sourceImage))
        .Return(1);

    filter.apply(sourceImage);

    Verify(Method(filterSpy, getDestinationImageWidth).Using(sourceImage));
    Verify(Method(filterSpy, getDestinationImageHeight).Using(sourceImage));
}
